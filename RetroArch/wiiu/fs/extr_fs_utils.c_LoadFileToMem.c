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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (scalar_t__) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int read (int,int /*<<< orphan*/ *,scalar_t__) ; 

int LoadFileToMem(const char *filepath, u8 **inbuffer, u32 *size)
{
   u8 *buffer;
   u32 filesize;
   int iFd;
   u32 blocksize = 0x4000;
   u32 done      = 0;
   int readBytes = 0;

   /* always initialze input */
   *inbuffer     = NULL;

   if (size)
      *size = 0;

   iFd = open(filepath, O_RDONLY);
   if (iFd < 0)
      return -1;

   filesize = lseek(iFd, 0, SEEK_END);
   lseek(iFd, 0, SEEK_SET);

   buffer = (u8 *) malloc(filesize);
   if (buffer == NULL)
   {
      close(iFd);
      return -2;
   }

   while(done < filesize)
   {
      if (done + blocksize > filesize)
         blocksize = filesize - done;
      readBytes = read(iFd, buffer + done, blocksize);
      if (readBytes <= 0)
         break;
      done += readBytes;
   }

   close(iFd);

   if (done != filesize)
   {
      free(buffer);
      return -3;
   }

   *inbuffer = buffer;

   /* sign is optional input */
   if (size)
      *size = filesize;

   return filesize;
}