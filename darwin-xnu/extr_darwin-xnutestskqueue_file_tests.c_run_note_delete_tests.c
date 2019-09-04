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
struct TYPE_4__ {int t_nondeterministic; int t_file_is_fifo; int /*<<< orphan*/ * t_cleanup_actions; int /*<<< orphan*/  t_helpthreadact; int /*<<< orphan*/ * t_prep_actions; } ;
typedef  TYPE_1__ test_t ;

/* Variables and functions */
 int /*<<< orphan*/  CREAT ; 
 scalar_t__ DIR1 ; 
 scalar_t__ DIR2 ; 
 scalar_t__ FILE1 ; 
 scalar_t__ FILE2 ; 
 int /*<<< orphan*/  MKDIR ; 
 int /*<<< orphan*/  MKFIFO ; 
 int /*<<< orphan*/  NOSLEEP ; 
 int /*<<< orphan*/  NOTE_DELETE ; 
 int /*<<< orphan*/  NOTHING ; 
 int /*<<< orphan*/  NO_EVENT ; 
 int /*<<< orphan*/  RENAME ; 
 int /*<<< orphan*/  RMDIR ; 
 int /*<<< orphan*/  SLEEP ; 
 int /*<<< orphan*/  SYMLINK ; 
 int /*<<< orphan*/  UNLINK ; 
 int /*<<< orphan*/  YES_EVENT ; 
 int /*<<< orphan*/  execute_test (TYPE_1__*) ; 
 int /*<<< orphan*/  init_action (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void*,...) ; 
 int /*<<< orphan*/  init_test (TYPE_1__*,char*,scalar_t__,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void 
run_note_delete_tests() 
{
	test_t test;
	
	init_test(&test, "1.1.2: unlink a file", FILE1, 1, 0, NOTE_DELETE, YES_EVENT);
	test.t_nondeterministic = 1;
	init_action(&(test.t_prep_actions[0]), NOSLEEP, CREAT, 2, (void*)FILE1, (void*)NULL);
	init_action(&test.t_helpthreadact, SLEEP, UNLINK, 2, (void*)FILE1, NULL);
	execute_test(&test);
	
	init_test(&test, "1.1.3: rmdir a dir", DIR1, 1, 0, NOTE_DELETE, YES_EVENT);
	test.t_nondeterministic = 1;
	init_action(&(test.t_prep_actions[0]), NOSLEEP, MKDIR, 2, (void*)DIR1, (void*)NULL);
	init_action(&test.t_helpthreadact, SLEEP, RMDIR, 2, (void*)DIR1, NULL);
	execute_test(&test);
	
	init_test(&test, "1.1.4: rename one file over another", FILE2, 2, 1, NOTE_DELETE, YES_EVENT);
	test.t_nondeterministic = 1;
	init_action(&(test.t_prep_actions[0]), NOSLEEP, CREAT, 2, (void*)FILE1, (void*)NULL);
	init_action(&(test.t_prep_actions[1]), NOSLEEP, CREAT, 2, (void*)FILE2, (void*)NULL);
	init_action(&test.t_helpthreadact, SLEEP, RENAME, 2, (void*)FILE1, (void*)FILE2);
	init_action(&test.t_cleanup_actions[0], NOSLEEP, UNLINK, 2, (void*)FILE2, NULL);
	execute_test(&test);
	
	init_test(&test, "1.1.5: rename one dir over another", DIR2, 2, 1, NOTE_DELETE, YES_EVENT);
	test.t_nondeterministic = 1;
	init_action(&(test.t_prep_actions[0]), NOSLEEP, MKDIR, 2, (void*)DIR1, (void*)NULL);
	init_action(&(test.t_prep_actions[1]), NOSLEEP, MKDIR, 2, (void*)DIR2, (void*)NULL);
	init_action(&test.t_helpthreadact, SLEEP, RENAME, 2, (void*)DIR1, (void*)DIR2);
	init_action(&test.t_cleanup_actions[0], NOSLEEP, RMDIR, 2, (void*)DIR2, NULL);
	execute_test(&test);
	
	/* Do FIFO stuff here */
	init_test(&test, "1.1.6: make a fifo, unlink it", FILE1, 1, 0, NOTE_DELETE, YES_EVENT);
	test.t_file_is_fifo = 1;
	init_action(&(test.t_prep_actions[0]), NOSLEEP, MKFIFO, 2, (void*)FILE1, (void*)NULL);
	init_action(&test.t_helpthreadact, SLEEP, UNLINK, 1, (void*)FILE1);
	execute_test(&test);
	
	init_test(&test, "1.1.7: rename a file over a fifo", FILE1, 2, 1, NOTE_DELETE, YES_EVENT);
	test.t_nondeterministic = 1;
	test.t_file_is_fifo = 1;
	init_action(&(test.t_prep_actions[0]), NOSLEEP, MKFIFO, 2, (void*)FILE1, (void*)NULL);
	init_action(&(test.t_prep_actions[1]), NOSLEEP, CREAT, 2, (void*)FILE2, (void*)NULL);
	init_action(&test.t_helpthreadact, SLEEP, RENAME, 2, (void*)FILE2, (void*)FILE1);
	init_action(&test.t_cleanup_actions[0], NOSLEEP, UNLINK, 2, (void*)FILE1, NULL);
	execute_test(&test);
	
	init_test(&test, "1.1.8: unlink a symlink to a file", FILE2, 2, 1, NOTE_DELETE, YES_EVENT);
	test.t_nondeterministic = 1;
	init_action(&(test.t_prep_actions[0]), NOSLEEP, CREAT, 2, (void*)FILE1, (void*)NULL);
	init_action(&(test.t_prep_actions[1]), NOSLEEP, SYMLINK, 2, (void*)FILE1, (void*)FILE2);
	init_action(&test.t_helpthreadact, SLEEP, UNLINK, 2, (void*)FILE2, NULL);
	init_action(&test.t_cleanup_actions[0], NOSLEEP, UNLINK, 2, (void*)FILE1, NULL);
	execute_test(&test);
	
	/* ================= */
	
	init_test(&test, "1.2.1: Straight-up rename file", FILE1, 1, 1, NOTE_DELETE, NO_EVENT);
	init_action(&(test.t_prep_actions[0]), NOSLEEP, CREAT, 2, (void*)FILE1, (void*)NULL);
	init_action(&test.t_helpthreadact, SLEEP, RENAME, 2, (void*)FILE1, (void*)FILE2); 
	init_action(&test.t_cleanup_actions[0], NOSLEEP, UNLINK, 2, (void*)FILE2, (void*)NULL);
	execute_test(&test);
	
	init_test(&test, "1.2.2: Straight-up rename dir", DIR1, 1, 1, NOTE_DELETE, NO_EVENT);
	init_action(&(test.t_prep_actions[0]), NOSLEEP, MKDIR, 2, (void*)DIR1, (void*)NULL);
	init_action(&test.t_helpthreadact, SLEEP, RENAME, 2, (void*)DIR1, (void*)DIR2); 
	init_action(&test.t_cleanup_actions[0], NOSLEEP, RMDIR, 2, (void*)DIR2, (void*)NULL);
	execute_test(&test);
	
	init_test(&test, "1.2.3: Null action on file", FILE1, 1, 1, NOTE_DELETE, NO_EVENT);
	init_action(&(test.t_prep_actions[0]), NOSLEEP, CREAT, 2, (void*)FILE1, (void*)NULL);
	init_action(&test.t_helpthreadact, SLEEP, NOTHING, 2, NULL, NULL); /* The null action */
	init_action(&test.t_cleanup_actions[0], NOSLEEP, UNLINK, 2, (void*)FILE1, (void*)NULL);
	execute_test(&test);
	
	init_test(&test, "1.2.4: Rename one file over another: watch the file that lives", FILE1, 2, 1, NOTE_DELETE, NO_EVENT);
	init_action(&(test.t_prep_actions[0]), NOSLEEP, CREAT, 2, (void*)FILE1, (void*)NULL);
	init_action(&(test.t_prep_actions[1]), NOSLEEP, CREAT, 2, (void*)FILE2, (void*)NULL);
	init_action(&test.t_helpthreadact, SLEEP, RENAME, 2, (void*)FILE1, (void*)FILE2);
	init_action(&test.t_cleanup_actions[0], NOSLEEP, UNLINK, 2, (void*)FILE2, NULL);
	execute_test(&test);
	
	init_test(&test, "1.2.5: Rename one dir over another, watch the dir that lives", DIR1, 2, 1, NOTE_DELETE, NO_EVENT);
	init_action(&(test.t_prep_actions[0]), NOSLEEP, MKDIR, 2, (void*)DIR1, (void*)NULL);
	init_action(&(test.t_prep_actions[1]), NOSLEEP, MKDIR, 2, (void*)DIR2, (void*)NULL);
	init_action(&test.t_helpthreadact, SLEEP, RENAME, 2, (void*)DIR1, (void*)DIR2);
	init_action(&test.t_cleanup_actions[0], NOSLEEP, RMDIR, 2, (void*)DIR2, NULL);
}