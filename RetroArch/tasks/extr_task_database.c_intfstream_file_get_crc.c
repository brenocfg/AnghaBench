#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  intfstream_t ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  RETRO_VFS_FILE_ACCESS_HINT_NONE ; 
 int /*<<< orphan*/  RETRO_VFS_FILE_ACCESS_READ ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intfstream_close (int /*<<< orphan*/ *) ; 
 int intfstream_get_crc (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * intfstream_open_file (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * intfstream_open_memory (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ intfstream_read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int intfstream_seek (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ intfstream_tell (int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (size_t) ; 

__attribute__((used)) static bool intfstream_file_get_crc(const char *name,
      uint64_t offset, size_t size, uint32_t *crc)
{
   int rv;
   intfstream_t *fd  = intfstream_open_file(name,
         RETRO_VFS_FILE_ACCESS_READ, RETRO_VFS_FILE_ACCESS_HINT_NONE);
   uint8_t *data     = NULL;
   int64_t file_size = -1;

   if (!fd)
      return 0;

   if (intfstream_seek(fd, 0, SEEK_END) == -1)
      goto error;

   file_size = intfstream_tell(fd);

   if (intfstream_seek(fd, 0, SEEK_SET) == -1)
      goto error;

   if (file_size < 0)
      goto error;

   if (offset != 0 || size < (uint64_t) file_size)
   {
      if (intfstream_seek(fd, (int64_t)offset, SEEK_SET) == -1)
         goto error;

      data = (uint8_t*)malloc(size);

      if (intfstream_read(fd, data, size) != (int64_t) size)
         goto error;

      intfstream_close(fd);
      free(fd);
      fd = intfstream_open_memory(data, RETRO_VFS_FILE_ACCESS_READ,
            RETRO_VFS_FILE_ACCESS_HINT_NONE, size);

      if (!fd)
         goto error;
   }

   rv = intfstream_get_crc(fd, crc);
   intfstream_close(fd);
   free(fd);
   free(data);
   return rv;

error:
   if (fd)
   {
      intfstream_close(fd);
      free(fd);
   }
   if (data)
      free(data);
   return 0;
}