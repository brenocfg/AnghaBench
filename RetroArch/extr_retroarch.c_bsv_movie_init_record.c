#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
struct TYPE_7__ {scalar_t__ size; } ;
typedef  TYPE_1__ retro_ctx_size_info_t ;
struct TYPE_8__ {int* data; int size; } ;
typedef  TYPE_2__ retro_ctx_serialize_info_t ;
typedef  int /*<<< orphan*/  intfstream_t ;
typedef  int /*<<< orphan*/  header ;
struct TYPE_9__ {int min_file_pos; int state_size; int* state; int /*<<< orphan*/ * file; } ;
typedef  TYPE_3__ bsv_movie_t ;

/* Variables and functions */
 int /*<<< orphan*/  BSV_MAGIC ; 
 size_t CRC_INDEX ; 
 size_t MAGIC_INDEX ; 
 int /*<<< orphan*/  RARCH_ERR (char*,...) ; 
 int /*<<< orphan*/  RETRO_VFS_FILE_ACCESS_HINT_NONE ; 
 int /*<<< orphan*/  RETRO_VFS_FILE_ACCESS_WRITE ; 
 size_t STATE_SIZE_INDEX ; 
 int content_get_crc () ; 
 int /*<<< orphan*/  core_serialize (TYPE_2__*) ; 
 int /*<<< orphan*/  core_serialize_size (TYPE_1__*) ; 
 int /*<<< orphan*/ * intfstream_open_file (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intfstream_write (int /*<<< orphan*/ *,int*,int) ; 
 scalar_t__ malloc (int) ; 
 int swap_if_big32 (int) ; 
 int swap_if_little32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool bsv_movie_init_record(
      bsv_movie_t *handle, const char *path)
{
   retro_ctx_size_info_t info;
   uint32_t state_size       = 0;
   uint32_t content_crc      = 0;
   uint32_t header[4]        = {0};
   intfstream_t *file        = intfstream_open_file(path,
         RETRO_VFS_FILE_ACCESS_WRITE,
         RETRO_VFS_FILE_ACCESS_HINT_NONE);

   if (!file)
   {
      RARCH_ERR("Could not open BSV file for recording, path : \"%s\".\n", path);
      return false;
   }

   handle->file             = file;

   content_crc              = content_get_crc();

   /* This value is supposed to show up as
    * BSV1 in a HEX editor, big-endian. */
   header[MAGIC_INDEX]      = swap_if_little32(BSV_MAGIC);
   header[CRC_INDEX]        = swap_if_big32(content_crc);

   core_serialize_size(&info);

   state_size               = (unsigned)info.size;

   header[STATE_SIZE_INDEX] = swap_if_big32(state_size);
#if 0
   RARCH_ERR("----- debug %u -----\n", header[0]);
   RARCH_ERR("----- debug %u -----\n", header[1]);
   RARCH_ERR("----- debug %u -----\n", header[2]);
   RARCH_ERR("----- debug %u -----\n", header[3]);
#endif

   intfstream_write(handle->file, header, 4 * sizeof(uint32_t));

   handle->min_file_pos     = sizeof(header) + state_size;
   handle->state_size       = state_size;

   if (state_size)
   {
      retro_ctx_serialize_info_t serial_info;

      handle->state = (uint8_t*)malloc(state_size);
      if (!handle->state)
         return false;

      serial_info.data = handle->state;
      serial_info.size = state_size;

      core_serialize(&serial_info);

      intfstream_write(handle->file,
            handle->state, state_size);
   }

   return true;
}