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
 int /*<<< orphan*/  InitFunctionPointers () ; 
 int /*<<< orphan*/  __fini () ; 
 int /*<<< orphan*/  __init () ; 
 int /*<<< orphan*/  fsdev_exit () ; 
 int /*<<< orphan*/  fsdev_init () ; 
 int main (int,char**) ; 
 int /*<<< orphan*/  memoryInitialize () ; 
 int /*<<< orphan*/  memoryRelease () ; 

int __entry_menu(int argc, char **argv)
{
   int ret;

   InitFunctionPointers();
   memoryInitialize();
   __init();
   fsdev_init();

   ret = main(argc, argv);

   fsdev_exit();
   __fini();
   memoryRelease();
   return ret;
}