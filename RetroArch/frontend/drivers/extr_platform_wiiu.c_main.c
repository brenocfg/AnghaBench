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
 int /*<<< orphan*/  get_arguments (int*,char***) ; 
 int /*<<< orphan*/  main_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  main_loop () ; 
 int /*<<< orphan*/  main_setup () ; 
 int /*<<< orphan*/  main_teardown () ; 
 int /*<<< orphan*/  rarch_main (int,char**,int /*<<< orphan*/ *) ; 

int main(int argc, char **argv)
{
   main_setup();
   get_arguments(&argc, &argv);

#ifdef IS_SALAMANDER
   int salamander_main(int argc, char **argv);
   salamander_main(argc, argv);
#else
   rarch_main(argc, argv, NULL);
   main_loop();
   main_exit(NULL);
#endif /* IS_SALAMANDER */
   main_teardown();

   /* We always return 0 because if we don't, it can prevent loading a
    * different RPX/ELF in HBL. */
   return 0;
}