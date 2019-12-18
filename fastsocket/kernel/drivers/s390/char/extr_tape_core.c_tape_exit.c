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
 int /*<<< orphan*/  DBF_EVENT (int,char*) ; 
 int /*<<< orphan*/  TAPE_DBF_AREA ; 
 int /*<<< orphan*/  debug_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tape_proc_cleanup () ; 
 int /*<<< orphan*/  tapeblock_exit () ; 
 int /*<<< orphan*/  tapechar_exit () ; 

__attribute__((used)) static void
tape_exit(void)
{
	DBF_EVENT(6, "tape exit\n");

	/* Get rid of the frontends */
	tapechar_exit();
	tapeblock_exit();
	tape_proc_cleanup();
	debug_unregister (TAPE_DBF_AREA);
}