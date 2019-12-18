#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_5__ {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ retro_ctx_serialize_info_t ;
struct TYPE_6__ {int did_rewind; int frame_ptr; scalar_t__* frame_pos; scalar_t__ min_file_pos; int frame_mask; int /*<<< orphan*/  file; int /*<<< orphan*/  state_size; int /*<<< orphan*/  state; int /*<<< orphan*/  playback; scalar_t__ first_rewind; } ;
typedef  TYPE_2__ bsv_movie_t ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 TYPE_2__* bsv_movie_state_handle ; 
 int /*<<< orphan*/  core_serialize (TYPE_1__*) ; 
 int /*<<< orphan*/  intfstream_seek (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 long intfstream_tell (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intfstream_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void bsv_movie_frame_rewind(void)
{
   bsv_movie_t *handle = bsv_movie_state_handle;

   if (!handle)
      return;

   handle->did_rewind = true;

   if (     (handle->frame_ptr <= 1)
         && (handle->frame_pos[0] == handle->min_file_pos))
   {
      /* If we're at the beginning... */
      handle->frame_ptr = 0;
      intfstream_seek(handle->file, (int)handle->min_file_pos, SEEK_SET);
   }
   else
   {
      /* First time rewind is performed, the old frame is simply replayed.
       * However, playing back that frame caused us to read data, and push
       * data to the ring buffer.
       *
       * Sucessively rewinding frames, we need to rewind past the read data,
       * plus another. */
      handle->frame_ptr = (handle->frame_ptr -
            (handle->first_rewind ? 1 : 2)) & handle->frame_mask;
      intfstream_seek(handle->file,
            (int)handle->frame_pos[handle->frame_ptr], SEEK_SET);
   }

   if (intfstream_tell(handle->file) <= (long)handle->min_file_pos)
   {
      /* We rewound past the beginning. */

      if (!handle->playback)
      {
         retro_ctx_serialize_info_t serial_info;

         /* If recording, we simply reset
          * the starting point. Nice and easy. */

         intfstream_seek(handle->file, 4 * sizeof(uint32_t), SEEK_SET);

         serial_info.data = handle->state;
         serial_info.size = handle->state_size;

         core_serialize(&serial_info);

         intfstream_write(handle->file, handle->state, handle->state_size);
      }
      else
         intfstream_seek(handle->file, (int)handle->min_file_pos, SEEK_SET);
   }
}