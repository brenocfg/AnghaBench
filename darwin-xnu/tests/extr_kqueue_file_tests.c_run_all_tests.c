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
 int /*<<< orphan*/  run_evfilt_read_tests () ; 
 int /*<<< orphan*/  run_evfilt_write_tests () ; 
 int /*<<< orphan*/  run_note_attrib_tests () ; 
 int /*<<< orphan*/  run_note_delete_tests () ; 
 int /*<<< orphan*/  run_note_extend_tests () ; 
 int /*<<< orphan*/  run_note_funlock_tests () ; 
 int /*<<< orphan*/  run_note_link_tests () ; 
 int /*<<< orphan*/  run_note_rename_tests () ; 
 int /*<<< orphan*/  run_note_revoke_tests () ; 
 int /*<<< orphan*/  run_note_write_tests () ; 
 int /*<<< orphan*/  run_poll_tests () ; 

void
run_all_tests() 
{
	run_note_delete_tests();
	run_note_write_tests();
	run_note_extend_tests();
	run_note_attrib_tests();
	run_note_link_tests();
	run_note_rename_tests();
#if 0
	run_note_revoke_tests(); /* Can no longer revoke a regular file--need an unmount test */
#endif /* 0 */
	run_evfilt_read_tests();
	run_evfilt_write_tests();
	run_poll_tests();
	run_note_funlock_tests();
}