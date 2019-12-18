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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ int64_t ;
typedef  int /*<<< orphan*/  RFILE ;

/* Variables and functions */
 int /*<<< orphan*/  CRC32_BUFFER_SIZE ; 
 unsigned int CRC32_MAX_MB ; 
 int /*<<< orphan*/  RETRO_VFS_FILE_ACCESS_READ ; 
 int /*<<< orphan*/  encoding_crc32 (int /*<<< orphan*/ ,unsigned char*,size_t) ; 
 int /*<<< orphan*/  filestream_close (int /*<<< orphan*/ *) ; 
 scalar_t__ filestream_eof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * filestream_open (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ filestream_read (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 scalar_t__ malloc (int /*<<< orphan*/ ) ; 

uint32_t file_crc32(uint32_t crc, const char *path)
{
   unsigned i;
   RFILE *file        = NULL;
   unsigned char *buf = NULL;
   if (!path)
      return 0;

   file = filestream_open(path, RETRO_VFS_FILE_ACCESS_READ, 0);
   if (!file)
      goto error;

   buf = (unsigned char*)malloc(CRC32_BUFFER_SIZE);
   if (!buf)
      goto error;

   for(i = 0; i < CRC32_MAX_MB; i++)
   {
      int64_t nread = filestream_read(file, buf, CRC32_BUFFER_SIZE);
      if (nread < 0)		
         goto error;

      crc = encoding_crc32(crc, buf, (size_t)nread);
      if (filestream_eof(file))
         break;
   }
   free(buf);
   filestream_close(file);
   return crc;

error:
   if (buf)
      free(buf);
   if (file)
      filestream_close(file);
   return 0;
}