#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int* Message_Digest; } ;
typedef  TYPE_1__ SHA1Context ;
typedef  int /*<<< orphan*/  RFILE ;

/* Variables and functions */
 int /*<<< orphan*/  RETRO_VFS_FILE_ACCESS_HINT_NONE ; 
 int /*<<< orphan*/  RETRO_VFS_FILE_ACCESS_READ ; 
 int /*<<< orphan*/  SHA1Input (TYPE_1__*,unsigned char*,int) ; 
 int /*<<< orphan*/  SHA1Reset (TYPE_1__*) ; 
 int /*<<< orphan*/  SHA1Result (TYPE_1__*) ; 
 int /*<<< orphan*/  filestream_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * filestream_open (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ filestream_read (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int,int,int,int) ; 

int sha1_calculate(const char *path, char *result)
{
   SHA1Context sha;
   unsigned char buff[4096];
   int rv    = 1;
   RFILE *fd = filestream_open(path,
         RETRO_VFS_FILE_ACCESS_READ,
         RETRO_VFS_FILE_ACCESS_HINT_NONE);

   if (!fd)
      goto error;

   buff[0] = '\0';

   SHA1Reset(&sha);

   do
   {
      rv = (int)filestream_read(fd, buff, 4096);
      if (rv < 0)
         goto error;

      SHA1Input(&sha, buff, rv);
   }while(rv);

   if (!SHA1Result(&sha))
      goto error;

   sprintf(result, "%08X%08X%08X%08X%08X",
         sha.Message_Digest[0],
         sha.Message_Digest[1],
         sha.Message_Digest[2],
         sha.Message_Digest[3], sha.Message_Digest[4]);

   filestream_close(fd);
   return 0;

error:
   if (fd)
      filestream_close(fd);
   return -1;
}