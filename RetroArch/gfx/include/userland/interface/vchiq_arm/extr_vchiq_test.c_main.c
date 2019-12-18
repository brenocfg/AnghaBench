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
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  main_process_pid ; 
 int vchiq_test (int,char**) ; 
 int /*<<< orphan*/  vcos_init () ; 
 scalar_t__ vcos_use_android_log ; 

int main(int argc, char **argv)
{
#ifdef ANDROID
   main_process_pid = getpid();
#endif

   vcos_init();
   vcos_use_android_log = 0;
   return vchiq_test(argc, argv);
}