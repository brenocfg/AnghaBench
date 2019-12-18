#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t uint32_t ;
typedef  int ssize_t ;
struct TYPE_6__ {size_t track_end; size_t offset; size_t frame_size; size_t track_start; size_t frames_per_hunk; scalar_t__ frame_offset; scalar_t__ hunkmem; scalar_t__ track_frame; int /*<<< orphan*/  chd; } ;
typedef  TYPE_1__ chdstream_t ;
struct TYPE_7__ {size_t unitbytes; } ;
typedef  TYPE_2__ chd_header ;

/* Variables and functions */
 TYPE_2__* chd_get_header (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chdstream_load_hunk (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,size_t) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 

ssize_t chdstream_read(chdstream_t *stream, void *data, size_t bytes)
{
   size_t end;
   uint32_t frame_offset;
   uint32_t hunk_offset;
   uint32_t chd_frame;
   uint32_t hunk;
   uint32_t amount;
   size_t data_offset   = 0;
   const chd_header *hd = chd_get_header(stream->chd);
   uint8_t         *out = (uint8_t*)data;

   if (stream->track_end - stream->offset < bytes)
      bytes = stream->track_end - stream->offset;

   end = stream->offset + bytes;
   while (stream->offset < end)
   {
      frame_offset = stream->offset % stream->frame_size;
      amount = stream->frame_size - frame_offset;
      if (amount > end - stream->offset)
         amount = (uint32_t)(end - stream->offset);

      /* In pregap */
      if (stream->offset < stream->track_start)
         memset(out + data_offset, 0, amount);
      else
      {
         chd_frame = (uint32_t)(stream->track_frame +
            (stream->offset - stream->track_start) / stream->frame_size);
         hunk = chd_frame / stream->frames_per_hunk;
         hunk_offset = (chd_frame % stream->frames_per_hunk) * hd->unitbytes;

         if (!chdstream_load_hunk(stream, hunk))
         {
            return -1;
         }
         memcpy(out + data_offset,
                stream->hunkmem + frame_offset
                + hunk_offset + stream->frame_offset, amount);
      }

      data_offset    += amount;
      stream->offset += amount;
   }

   return bytes;
}