#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int t_nondeterministic; int /*<<< orphan*/ * t_cleanup_actions; int /*<<< orphan*/  t_helpthreadact; int /*<<< orphan*/ * t_prep_actions; } ;
typedef  TYPE_1__ test_t ;

/* Variables and functions */
 int /*<<< orphan*/  CREAT ; 
 scalar_t__ DIR1 ; 
 scalar_t__ DIR2 ; 
 scalar_t__ FILE1 ; 
 scalar_t__ FILE2 ; 
 int /*<<< orphan*/  HARDLINK ; 
 int /*<<< orphan*/  MKDIR ; 
 int /*<<< orphan*/  NOSLEEP ; 
 int /*<<< orphan*/  NOTE_RENAME ; 
 int /*<<< orphan*/  NO_EVENT ; 
 int /*<<< orphan*/  RENAME ; 
 int /*<<< orphan*/  RMDIR ; 
 int /*<<< orphan*/  SLEEP ; 
 int /*<<< orphan*/  UNLINK ; 
 int /*<<< orphan*/  YES_EVENT ; 
 int /*<<< orphan*/  execute_test (TYPE_1__*) ; 
 int /*<<< orphan*/  init_action (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void*,void*) ; 
 int /*<<< orphan*/  init_test (TYPE_1__*,char*,scalar_t__,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
run_note_rename_tests() 
{
	test_t test;
	
	init_test(&test, "6.1.1: rename a file", FILE1, 1, 1, NOTE_RENAME, YES_EVENT);
	test.t_nondeterministic = 1;
	init_action(&(test.t_prep_actions[0]), NOSLEEP, CREAT, 2, (void*)FILE1, (void*)NULL);
	init_action(&test.t_helpthreadact, SLEEP, RENAME, 2, (void*)FILE1, (void*)FILE2);
	init_action(&test.t_cleanup_actions[0], NOSLEEP, UNLINK, 2, (void*)FILE2, NULL);
	execute_test(&test);
	
	init_test(&test, "6.1.2: rename a dir", DIR1, 1, 1, NOTE_RENAME, YES_EVENT);
	test.t_nondeterministic = 1;
	init_action(&(test.t_prep_actions[0]), NOSLEEP, MKDIR, 2, (void*)DIR1, (void*)NULL);
	init_action(&test.t_helpthreadact, SLEEP, RENAME, 2, (void*)DIR1, (void*)DIR2);
	init_action(&test.t_cleanup_actions[0], NOSLEEP, RMDIR, 2, (void*)DIR2, NULL);
	execute_test(&test);
	
	init_test(&test, "6.1.3: rename one file over another", FILE1, 2, 1, NOTE_RENAME, YES_EVENT);
	init_action(&(test.t_prep_actions[0]), NOSLEEP, CREAT, 2, (void*)FILE1, (void*)NULL);
	init_action(&(test.t_prep_actions[1]), NOSLEEP, CREAT, 2, (void*)FILE2, (void*)NULL);
	init_action(&test.t_helpthreadact, SLEEP, RENAME, 2, (void*)FILE1, (void*)FILE2);
	init_action(&test.t_cleanup_actions[0], NOSLEEP, UNLINK, 2, (void*)FILE2, NULL);
	execute_test(&test);
	
	init_test(&test, "6.1.4: rename one dir over another", DIR1, 2, 1, NOTE_RENAME, YES_EVENT);
	test.t_nondeterministic = 1;
	init_action(&(test.t_prep_actions[0]), NOSLEEP, MKDIR, 2, (void*)DIR1, (void*)NULL);
	init_action(&(test.t_prep_actions[1]), NOSLEEP, MKDIR, 2, (void*)DIR2, (void*)NULL);
	init_action(&test.t_helpthreadact, SLEEP, RENAME, 2, (void*)DIR1, (void*)DIR2);
	init_action(&test.t_cleanup_actions[0], NOSLEEP, RMDIR, 2, (void*)DIR2, NULL);
	execute_test(&test);
	
	/* ========= NO EVENT SECTION =========== */
	
	init_test(&test, "6.2.1: unlink a file", FILE1, 1, 0, NOTE_RENAME, NO_EVENT);
	init_action(&(test.t_prep_actions[0]), NOSLEEP, CREAT, 2, (void*)FILE1, (void*)NULL);
	init_action(&test.t_helpthreadact, SLEEP, UNLINK, 2, (void*)FILE1, NULL);
	execute_test(&test);
	
	init_test(&test, "6.2.2: rmdir a dir", DIR1, 1, 0, NOTE_RENAME, NO_EVENT);
	init_action(&(test.t_prep_actions[0]), NOSLEEP, MKDIR, 2, (void*)DIR1, (void*)NULL);
	init_action(&test.t_helpthreadact, SLEEP, RMDIR, 2, (void*)DIR1, NULL);
	execute_test(&test);
	
	init_test(&test, "6.2.3: link() to a file", FILE1, 1, 2, NOTE_RENAME, NO_EVENT);
	init_action(&(test.t_prep_actions[0]), NOSLEEP, CREAT, 2, (void*)FILE1, (void*)NULL);
	init_action(&test.t_helpthreadact, SLEEP, HARDLINK, 2, (void*)FILE1, (void*)FILE2);
	init_action(&test.t_cleanup_actions[0], NOSLEEP, UNLINK, 2, (void*)FILE1, NULL);
	init_action(&test.t_cleanup_actions[1], NOSLEEP, UNLINK, 2, (void*)FILE2, NULL);
	execute_test(&test);
	
	init_test(&test, "6.2.4: rename one file over another: watch deceased", 
			  FILE2, 2, 1, NOTE_RENAME, NO_EVENT);
	init_action(&(test.t_prep_actions[0]), NOSLEEP, CREAT, 2, (void*)FILE1, (void*)NULL);
	init_action(&(test.t_prep_actions[1]), NOSLEEP, CREAT, 2, (void*)FILE2, (void*)NULL);
	init_action(&test.t_helpthreadact, SLEEP, RENAME, 2, (void*)FILE1, (void*)FILE2);
	init_action(&test.t_cleanup_actions[0], NOSLEEP, UNLINK, 2, (void*)FILE2, NULL);
	execute_test(&test);
	
	init_test(&test, "6.2.5: rename one dir over another: watch deceased", 
			  DIR2, 2, 1, NOTE_RENAME, NO_EVENT);
	init_action(&(test.t_prep_actions[0]), NOSLEEP, MKDIR, 2, (void*)DIR1, (void*)NULL);
	init_action(&(test.t_prep_actions[1]), NOSLEEP, MKDIR, 2, (void*)DIR2, (void*)NULL);
	init_action(&test.t_helpthreadact, SLEEP, RENAME, 2, (void*)DIR1, (void*)DIR2);
	init_action(&test.t_cleanup_actions[0], NOSLEEP, RMDIR, 2, (void*)DIR2, NULL);
	execute_test(&test);
	
	init_test(&test, "6.2.6: rename a file to itself", FILE1, 1, 1, NOTE_RENAME, NO_EVENT);
	init_action(&(test.t_prep_actions[0]), NOSLEEP, CREAT, 2, (void*)FILE1, (void*)NULL);
	init_action(&test.t_helpthreadact, SLEEP, RENAME, 2, (void*)FILE1, (void*)FILE1);
	init_action(&test.t_cleanup_actions[0], NOSLEEP, UNLINK, 2, (void*)FILE1, NULL);
	execute_test(&test);
	
	init_test(&test, "6.2.7: rename a dir to itself", DIR1, 1, 1, NOTE_RENAME, NO_EVENT);
	init_action(&(test.t_prep_actions[0]), NOSLEEP, MKDIR, 2, (void*)DIR1, (void*)NULL);
	init_action(&test.t_helpthreadact, SLEEP, RENAME, 2, (void*)DIR1, (void*)DIR1);
	init_action(&test.t_cleanup_actions[0], NOSLEEP, RMDIR, 2, (void*)DIR1, NULL);
	execute_test(&test);
}