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
typedef  size_t u32 ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  MappedMemoryReadByte (size_t) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fwrite (void*,int,size_t,int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (size_t) ; 

int MappedMemorySave(const char *filename, u32 addr, u32 size)
{
   FILE *fp;
   u8 *buffer;
   u32 i;

   if (!filename)
      return -1;

   if ((fp = fopen(filename, "wb")) == NULL)
      return -1;

   if ((buffer = (u8 *)malloc(size)) == NULL)
   {
      fclose(fp);
      return -2;
   }

   for (i = 0; i < size; i++)
      buffer[i] = MappedMemoryReadByte(addr+i);

   fwrite((void *)buffer, 1, size, fp);
   fclose(fp);
   free(buffer);

   return 0;
}