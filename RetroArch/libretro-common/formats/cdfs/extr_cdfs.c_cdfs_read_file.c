#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint64_t ;
typedef  size_t int64_t ;
struct TYPE_4__ {scalar_t__ first_sector; size_t size; size_t pos; int sector_buffer_valid; int current_sector_offset; void* sector_buffer; scalar_t__ current_sector; TYPE_2__* track; } ;
typedef  TYPE_1__ cdfs_file_t ;
struct TYPE_5__ {int /*<<< orphan*/  stream; } ;

/* Variables and functions */
 int /*<<< orphan*/  cdfs_seek_track_sector (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  intfstream_read (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  memcpy (void*,void*,size_t) ; 

int64_t cdfs_read_file(cdfs_file_t* file, void* buffer, uint64_t len)
{
   int bytes_read = 0;

   if (!file || file->first_sector < 0 || !buffer)
      return 0;

   if (len > file->size - file->pos)
      len = file->size - file->pos;

   if (len == 0)
      return 0;

   if (file->sector_buffer_valid)
   {
      size_t remaining = 2048 - file->current_sector_offset;
      if (remaining > 0)
      {
         if (remaining >= len)
         {
            memcpy(buffer, &file->sector_buffer[file->current_sector_offset], len);
            file->current_sector_offset += len;
            return len;
         }

         memcpy(buffer, &file->sector_buffer[file->current_sector_offset], remaining);
         buffer = (char*)buffer + remaining;
         bytes_read += remaining;
         len -= remaining;

         file->current_sector_offset += remaining;
      }

      ++file->current_sector;
      file->current_sector_offset = 0;
      file->sector_buffer_valid = 0;
   }
   else if (file->current_sector < file->first_sector)
   {
      file->current_sector = file->first_sector;
      file->current_sector_offset = 0;
   }

   while (len >= 2048)
   {
      cdfs_seek_track_sector(file->track, file->current_sector);
      intfstream_read(file->track->stream, buffer, 2048);

      buffer = (char*)buffer + 2048;
      bytes_read += 2048;
      ++file->current_sector;

      len -= 2048;
   }

   if (len > 0)
   {
      cdfs_seek_track_sector(file->track, file->current_sector);
      intfstream_read(file->track->stream, file->sector_buffer, 2048);
      memcpy(buffer, file->sector_buffer, len);
      file->current_sector_offset = len;
      file->sector_buffer_valid   = 1;

      bytes_read += len;
   }

   file->pos += bytes_read;
   return bytes_read;
}