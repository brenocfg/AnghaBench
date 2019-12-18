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

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void usage(void)
{
   printf("Usage:\n");
   printf("    dtmerge [<options] <base dtb> <merged dtb> - [param=value] ...\n");
   printf("        to apply a parameter to the base dtb (like dtparam)\n");
   printf("    dtmerge [<options] <base dtb> <merged dtb> <overlay dtb> [param=value] ...\n");
   printf("        to apply an overlay with parameters (like dtoverlay)\n");
   printf("  where <options> is any of:\n");
   printf("    -d      Enable debug output\n");
   printf("    -h      Show this help message\n");
   exit(1);
}