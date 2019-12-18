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
 int /*<<< orphan*/  enter_cap_mode (int,char**) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  get_opt (int*,char***) ; 
 int /*<<< orphan*/  global_dest () ; 
 int /*<<< orphan*/  global_init () ; 
 int read_files (int,char**) ; 

int
main(int argc, char **argv)
{
	int rtn;

	global_init();
	get_opt(&argc, &argv);
	enter_cap_mode(argc, argv);
	rtn = read_files(argc, argv);
	global_dest();

	exit(rtn);
}