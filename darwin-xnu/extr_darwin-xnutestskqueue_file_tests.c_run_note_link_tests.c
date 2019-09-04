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
struct TYPE_4__ {int t_nondeterministic; int t_known_failure; int /*<<< orphan*/ * t_cleanup_actions; int /*<<< orphan*/  t_helpthreadact; int /*<<< orphan*/ * t_prep_actions; } ;
typedef  TYPE_1__ test_t ;

/* Variables and functions */
 int /*<<< orphan*/  CREAT ; 
 scalar_t__ DIR1 ; 
 scalar_t__ DIR2 ; 
 scalar_t__ DOTDOT ; 
 scalar_t__ FILE1 ; 
 scalar_t__ FILE2 ; 
 int /*<<< orphan*/  HARDLINK ; 
 int /*<<< orphan*/  MKDIR ; 
 int /*<<< orphan*/  NOSLEEP ; 
 int /*<<< orphan*/  NOTE_LINK ; 
 int /*<<< orphan*/  NO_EVENT ; 
 int /*<<< orphan*/  RENAME ; 
 int /*<<< orphan*/  RMDIR ; 
 int /*<<< orphan*/  SLEEP ; 
 int /*<<< orphan*/  SYMLINK ; 
 int /*<<< orphan*/  T_LOG (char*) ; 
 int /*<<< orphan*/  UNLINK ; 
 int /*<<< orphan*/  YES_EVENT ; 
 int /*<<< orphan*/  execute_test (TYPE_1__*) ; 
 int /*<<< orphan*/  init_action (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void*,void*) ; 
 int /*<<< orphan*/  init_test (TYPE_1__*,char*,scalar_t__,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  makepath (char*,scalar_t__,scalar_t__) ; 

void 
run_note_link_tests()
{
	test_t test;
	char pathbuf[50];
	char otherpathbuf[50];
	
	T_LOG("HFS DOES NOT HANDLE UNLINK CORRECTLY...\n");
	init_test(&test, "5.1.1: unlink() a file", FILE1, 1, 0, NOTE_LINK, YES_EVENT);
	test.t_nondeterministic = 1;
	init_action(&(test.t_prep_actions[0]), NOSLEEP, CREAT, 2, (void*)FILE1, (void*)NULL);
	init_action(&test.t_helpthreadact, SLEEP, UNLINK, 2, (void*)FILE1, (void*)NULL);
	execute_test(&test);
	
	
	init_test(&test, "5.1.1.5: link A to B, watch A, remove B", FILE1, 2, 1, NOTE_LINK, YES_EVENT);
	init_action(&(test.t_prep_actions[0]), NOSLEEP, CREAT, 2, (void*)FILE1, (void*)NULL);
	init_action(&(test.t_prep_actions[1]), NOSLEEP, HARDLINK, 2, (void*)FILE1, (void*)FILE2);
	init_action(&test.t_helpthreadact, SLEEP, UNLINK, 2, (void*)FILE2, (void*)NULL);
	init_action(&test.t_cleanup_actions[0], NOSLEEP, UNLINK, 2, (void*)FILE1, NULL);
	execute_test(&test);
	
	init_test(&test, "5.1.2: link() to a file", FILE1, 1, 2, NOTE_LINK, YES_EVENT);
#if TARGET_OS_WATCH
	test.t_nondeterministic = 1;
#endif
	init_action(&(test.t_prep_actions[0]), NOSLEEP, CREAT, 2, (void*)FILE1, (void*)NULL);
	init_action(&test.t_helpthreadact, SLEEP, HARDLINK, 2, (void*)FILE1, (void*)FILE2);
	init_action(&test.t_cleanup_actions[0], NOSLEEP, UNLINK, 2, (void*)FILE1, NULL);
	init_action(&test.t_cleanup_actions[1], NOSLEEP, UNLINK, 2, (void*)FILE2, NULL);
	execute_test(&test);
	
	makepath(pathbuf, DIR1, DIR2);
	init_test(&test, "5.1.3: make one dir in another", DIR1, 1, 2, NOTE_LINK, YES_EVENT);
	test.t_known_failure = 1;
	init_action(&(test.t_prep_actions[0]), NOSLEEP, MKDIR, 2, (void*)DIR1, (void*)NULL);
	init_action(&test.t_helpthreadact, SLEEP, MKDIR, 2, (void*)pathbuf, (void*)NULL);
	init_action(&test.t_cleanup_actions[0], NOSLEEP, RMDIR, 2, (void*)pathbuf, NULL);
	init_action(&test.t_cleanup_actions[1], NOSLEEP, RMDIR, 2, (void*)DIR1, NULL);
	execute_test(&test);
	
	makepath(pathbuf, DIR1, DIR2);
	init_test(&test, "5.1.4: rmdir a dir from within another", DIR1, 2, 1, NOTE_LINK, YES_EVENT);
	test.t_known_failure = 1;
	init_action(&(test.t_prep_actions[0]), NOSLEEP, MKDIR, 2, (void*)DIR1, (void*)NULL);
	init_action(&(test.t_prep_actions[1]), NOSLEEP, MKDIR, 2, (void*)pathbuf, (void*)NULL);
	init_action(&test.t_helpthreadact, SLEEP, RMDIR, 2, (void*)pathbuf, (void*)NULL);
	init_action(&test.t_cleanup_actions[0], NOSLEEP, RMDIR, 2, (void*)DIR1, NULL);
	execute_test(&test);
	
	makepath(pathbuf, DIR1, DIR2);
	makepath(otherpathbuf, DIR1, DIR1);
	init_test(&test, "5.1.5: rename dir A over dir B inside dir C", DIR1, 3, 2, NOTE_LINK, YES_EVENT);
	test.t_known_failure = 1;
	init_action(&(test.t_prep_actions[0]), NOSLEEP, MKDIR, 2, (void*)DIR1, (void*)NULL);
	init_action(&(test.t_prep_actions[1]), NOSLEEP, MKDIR, 2, (void*)pathbuf, (void*)NULL);
	init_action(&(test.t_prep_actions[2]), NOSLEEP, MKDIR, 2, (void*)otherpathbuf, (void*)NULL);
	init_action(&test.t_helpthreadact, SLEEP, RENAME, 2, (void*)pathbuf, (void*)otherpathbuf);
	init_action(&test.t_cleanup_actions[0], NOSLEEP, RMDIR, 2, (void*)otherpathbuf, NULL);
	init_action(&test.t_cleanup_actions[1], NOSLEEP, RMDIR, 2, (void*)DIR1, NULL);
	execute_test(&test);
	
	T_LOG("HFS bypasses hfs_makenode to create in target, so misses knote.\n");
	makepath(pathbuf, DIR1, DIR2);
	init_test(&test, "5.1.6: rename one dir into another", DIR1, 2, 2, NOTE_LINK, YES_EVENT);
	test.t_known_failure = 1;
	init_action(&(test.t_prep_actions[0]), NOSLEEP, MKDIR, 2, (void*)DIR1, (void*)NULL);
	init_action(&(test.t_prep_actions[1]), NOSLEEP, MKDIR, 2, (void*)DIR2, (void*)NULL);
	init_action(&test.t_helpthreadact, SLEEP, RENAME, 2, (void*)DIR2, (void*)pathbuf);
	init_action(&test.t_cleanup_actions[0], NOSLEEP, RMDIR, 2, (void*)pathbuf, NULL);
	init_action(&test.t_cleanup_actions[1], NOSLEEP, RMDIR, 2, (void*)DIR1, NULL);
	execute_test(&test);
	
	T_LOG("HFS bypasses hfs_removedir to remove from source, so misses knote.\n");
	makepath(pathbuf, DIR1, DIR2);
	init_test(&test, "5.1.7: rename one dir out of another", DIR1, 2, 2, NOTE_LINK, YES_EVENT);
	test.t_known_failure = 1;
	init_action(&(test.t_prep_actions[0]), NOSLEEP, MKDIR, 2, (void*)DIR1, (void*)NULL);
	init_action(&(test.t_prep_actions[1]), NOSLEEP, MKDIR, 2, (void*)pathbuf, (void*)NULL);
	init_action(&test.t_helpthreadact, SLEEP, RENAME, 2, (void*)pathbuf, (void*)DIR2);
	init_action(&test.t_cleanup_actions[0], NOSLEEP, RMDIR, 2, (void*)DIR2, NULL);
	init_action(&test.t_cleanup_actions[1], NOSLEEP, RMDIR, 2, (void*)DIR1, NULL);
	execute_test(&test);
	
	init_test(&test, "5.1.8: rmdir a dir", DIR1, 1, 0, NOTE_LINK, YES_EVENT);
	test.t_nondeterministic = 1;
	init_action(&(test.t_prep_actions[0]), NOSLEEP, MKDIR, 2, (void*)DIR1, (void*)NULL);
	init_action(&test.t_helpthreadact, SLEEP, RMDIR, 2, (void*)DIR1, (void*)NULL);
	execute_test(&test);
	
	/* ============= NO EVENT SECTION ============== */
	makepath(pathbuf, DIR1, FILE1);
	init_test(&test, "5.2.1: make a file in a dir", DIR1, 1, 2, NOTE_LINK, NO_EVENT);
	test.t_known_failure = 1;
	init_action(&(test.t_prep_actions[0]), NOSLEEP, MKDIR, 2, (void*)DIR1, (void*)NULL);
	init_action(&test.t_helpthreadact, SLEEP, CREAT, 2, (void*)pathbuf, (void*)NULL);
	init_action(&test.t_cleanup_actions[0], NOSLEEP, UNLINK, 2, (void*)pathbuf, NULL);
	init_action(&test.t_cleanup_actions[1], NOSLEEP, RMDIR, 2, (void*)DIR1, NULL);
	execute_test(&test);
	
	makepath(pathbuf, DIR1, FILE1);
	init_test(&test, "5.2.2: unlink a file in a dir", DIR1, 2, 1, NOTE_LINK, NO_EVENT);
	test.t_known_failure = 1;
	init_action(&(test.t_prep_actions[0]), NOSLEEP, MKDIR, 2, (void*)DIR1, (void*)NULL);
	init_action(&(test.t_prep_actions[1]), NOSLEEP, CREAT, 2, (void*)pathbuf, (void*)NULL);
	init_action(&test.t_helpthreadact, SLEEP, UNLINK, 2, (void*)pathbuf, (void*)NULL);
	init_action(&test.t_cleanup_actions[0], NOSLEEP, RMDIR, 2, (void*)DIR1, NULL);
	execute_test(&test);
	
	makepath(pathbuf, DIR1, FILE1);
	makepath(otherpathbuf, DIR1, FILE2);
	init_test(&test, "5.2.3: rename a file within a dir", DIR1, 2, 2, NOTE_LINK, NO_EVENT);
	test.t_known_failure = 1;
	init_action(&(test.t_prep_actions[0]), NOSLEEP, MKDIR, 2, (void*)DIR1, (void*)NULL);
	init_action(&(test.t_prep_actions[1]), NOSLEEP, CREAT, 2, (void*)pathbuf, (void*)NULL);
	init_action(&test.t_helpthreadact, SLEEP, RENAME, 2, (void*)pathbuf, (void*)otherpathbuf);
	init_action(&test.t_cleanup_actions[0], NOSLEEP, UNLINK, 2, (void*)otherpathbuf, NULL);
	init_action(&test.t_cleanup_actions[1], NOSLEEP, RMDIR, 2, (void*)DIR1, NULL);
	execute_test(&test);
	
	makepath(pathbuf, DIR1, FILE1);
	init_test(&test, "5.2.4: rename a file into a dir", DIR1, 2, 2, NOTE_LINK, NO_EVENT);
	test.t_known_failure = 1;
	init_action(&(test.t_prep_actions[0]), NOSLEEP, MKDIR, 2, (void*)DIR1, (void*)NULL);
	init_action(&(test.t_prep_actions[1]), NOSLEEP, CREAT, 2, (void*)FILE1, (void*)NULL);
	init_action(&test.t_helpthreadact, SLEEP, RENAME, 2, (void*)FILE1, (void*)pathbuf);
	init_action(&test.t_cleanup_actions[0], NOSLEEP, UNLINK, 2, (void*)pathbuf, NULL);
	init_action(&test.t_cleanup_actions[1], NOSLEEP, RMDIR, 2, (void*)DIR1, NULL);
	execute_test(&test);
	
	makepath(pathbuf, DIR1, FILE1);
	init_test(&test, "5.2.5: make a symlink in a dir", DIR1, 1, 2, NOTE_LINK, NO_EVENT);
	test.t_known_failure = 1;
	init_action(&(test.t_prep_actions[0]), NOSLEEP, MKDIR, 2, (void*)DIR1, (void*)NULL);
	init_action(&test.t_helpthreadact, SLEEP, SYMLINK, 2, (void*)DOTDOT, (void*)pathbuf);
	init_action(&test.t_cleanup_actions[0], NOSLEEP, UNLINK, 2, (void*)pathbuf, NULL);
	init_action(&test.t_cleanup_actions[1], NOSLEEP, RMDIR, 2, (void*)DIR1, NULL);
	execute_test(&test);
	
	init_test(&test, "5.2.6: make a symlink to a dir", DIR1, 1, 2, NOTE_LINK, NO_EVENT);
	test.t_known_failure = 1;
	init_action(&(test.t_prep_actions[0]), NOSLEEP, MKDIR, 2, (void*)DIR1, (void*)NULL);
	init_action(&test.t_helpthreadact, SLEEP, SYMLINK, 2, (void*)DIR1, (void*)FILE1);
	init_action(&test.t_cleanup_actions[0], NOSLEEP, UNLINK, 2, (void*)FILE1, NULL);
	init_action(&test.t_cleanup_actions[1], NOSLEEP, RMDIR, 2, (void*)DIR1, NULL);
	execute_test(&test);
	
	init_test(&test, "5.2.7: make a symlink to a file", FILE1, 1, 2, NOTE_LINK, NO_EVENT);
	init_action(&(test.t_prep_actions[0]), NOSLEEP, CREAT, 2, (void*)FILE1, (void*)NULL);
	init_action(&test.t_helpthreadact, SLEEP, SYMLINK, 2, (void*)FILE1, (void*)FILE2);
	init_action(&test.t_cleanup_actions[0], NOSLEEP, UNLINK, 2, (void*)FILE2, NULL);
	init_action(&test.t_cleanup_actions[1], NOSLEEP, UNLINK, 2, (void*)FILE1, NULL);
	execute_test(&test);
}