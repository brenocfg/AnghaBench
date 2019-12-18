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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_ERR (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fscanf (int /*<<< orphan*/ *,char*,unsigned int*) ; 

__attribute__((used)) static unsigned int get_memory_size(void)
{
   FILE *size_fp;
   unsigned int size;

   /* this file holds the memory range needed to map the framebuffer into
    * kernel address space, it is specified in the device tree
    */
   size_fp = fopen("/sys/class/uio/uio0/maps/map0/size", "r");

   if (!size_fp)
   {
      RARCH_ERR("unable to open the uio size file\n");
      exit(1);
   }

   fscanf(size_fp, "0x%08X", &size);
   fclose(size_fp);

   return size;
}