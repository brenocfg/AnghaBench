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
struct passwd {scalar_t__ pw_gid; scalar_t__ pw_uid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHMOD ; 
 int /*<<< orphan*/  CHOWN ; 
 int /*<<< orphan*/  CREAT ; 
 void* DIR1 ; 
 void* DIR2 ; 
 scalar_t__ DOTDOT ; 
 int /*<<< orphan*/  EXCHANGEDATA ; 
 void* FILE1 ; 
 scalar_t__ FILE2 ; 
 int /*<<< orphan*/  MKDIR ; 
 int /*<<< orphan*/  MKFIFO ; 
 int /*<<< orphan*/  NOSLEEP ; 
 int /*<<< orphan*/  NOTE_ATTRIB ; 
 int /*<<< orphan*/  NO_EVENT ; 
 int /*<<< orphan*/  OPEN ; 
 int /*<<< orphan*/  PDIR ; 
 int /*<<< orphan*/  RENAME ; 
 int /*<<< orphan*/  RMDIR ; 
 int /*<<< orphan*/  SETXATTR ; 
 int /*<<< orphan*/  SLEEP ; 
 int /*<<< orphan*/  STAT ; 
 int /*<<< orphan*/  SYMLINK ; 
 int /*<<< orphan*/  T_LOG (char*) ; 
 int /*<<< orphan*/  UNLINK ; 
 int /*<<< orphan*/  UTIMES ; 
 int /*<<< orphan*/  WRITE ; 
 int /*<<< orphan*/  YES_EVENT ; 
 int /*<<< orphan*/  execute_test (TYPE_1__*) ; 
 scalar_t__ getgid () ; 
 struct passwd* getpwnam (char*) ; 
 scalar_t__ getuid () ; 
 int /*<<< orphan*/  init_action (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void*,...) ; 
 int /*<<< orphan*/  init_test (TYPE_1__*,char*,void*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  makepath (char*,void*,void*) ; 
 int /*<<< orphan*/  path_on_apfs (int /*<<< orphan*/ ) ; 

void
run_note_attrib_tests()
{
	test_t test;
	char pathbuf[50];
	
	init_test(&test, "4.1.1: chmod a file", FILE1, 1, 1, NOTE_ATTRIB, YES_EVENT);
	test.t_nondeterministic = 1;
	init_action(&(test.t_prep_actions[0]), NOSLEEP, CREAT, 2, (void*)FILE1, (void*)NULL);
	init_action(&test.t_helpthreadact, SLEEP, CHMOD, 2, FILE1, (void*)0700); 
	init_action(&test.t_cleanup_actions[0], NOSLEEP, UNLINK, 2, (void*)FILE1, (void*)NULL);
	execute_test(&test);
	
	struct passwd *pwd = getpwnam("local");
	if (pwd != NULL) {
		init_test(&test, "4.1.2: chown a file", FILE1, 2, 1, NOTE_ATTRIB, YES_EVENT);
		init_action(&(test.t_prep_actions[0]), NOSLEEP, CREAT, 2, (void*)FILE1, (void*)NULL);
		init_action(&(test.t_prep_actions[1]), NOSLEEP, CHOWN, 3, (void*)FILE1, (void*)pwd->pw_uid, (void*)pwd->pw_gid);
		init_action(&test.t_helpthreadact, SLEEP, CHOWN, 3, FILE1, (void*)getuid(), (void*)pwd->pw_gid);
		init_action(&test.t_cleanup_actions[0], NOSLEEP, UNLINK, 2, (void*)FILE1, (void*)NULL);
		execute_test(&test);
	}

	init_test(&test, "4.1.3: chmod a dir", DIR1, 1, 1, NOTE_ATTRIB, YES_EVENT);
	init_action(&(test.t_prep_actions[0]), NOSLEEP, MKDIR, 2, (void*)DIR1, (void*)NULL);
	init_action(&(test.t_helpthreadact), SLEEP, CHMOD, 2, (void*)DIR1, (void*)0700);
	init_action(&test.t_cleanup_actions[0], NOSLEEP, RMDIR, 2, (void*)DIR1, (void*)NULL);
	execute_test(&test);
	
	if (pwd != NULL) {
		init_test(&test, "4.1.4: chown a dir", DIR1, 2, 1, NOTE_ATTRIB, YES_EVENT);
		init_action(&(test.t_prep_actions[0]), NOSLEEP, MKDIR, 2, (void*)DIR1, (void*)NULL);
		init_action(&(test.t_prep_actions[1]), NOSLEEP, CHOWN, 3, (void*)DIR1, (void*) pwd->pw_uid, (void*)pwd->pw_gid);
		init_action(&test.t_helpthreadact, SLEEP, CHOWN, 3, DIR1, (void*)getuid(), (void*)getgid());
		init_action(&test.t_cleanup_actions[0], NOSLEEP, RMDIR, 2, (void*)DIR1, (void*)NULL);
		execute_test(&test);
	}
	
	init_test(&test, "4.1.5: setxattr on a file", FILE1, 1, 1, NOTE_ATTRIB, YES_EVENT);
	test.t_nondeterministic = 1;
	init_action(&(test.t_prep_actions[0]), NOSLEEP, CREAT, 2, (void*)FILE1, (void*)NULL);
	init_action(&test.t_helpthreadact, SLEEP, SETXATTR, 2, (void*)FILE1, (void*)NULL); 
	init_action(&test.t_cleanup_actions[0], NOSLEEP, UNLINK, 2, (void*)FILE1, (void*)NULL);
	execute_test(&test);
	
	init_test(&test, "4.1.6: setxattr on a dir", DIR1, 1, 1, NOTE_ATTRIB, YES_EVENT);
	test.t_nondeterministic = 1;
	init_action(&(test.t_prep_actions[0]), NOSLEEP, MKDIR, 2, (void*)DIR1, (void*)NULL);
	init_action(&test.t_helpthreadact, SLEEP, SETXATTR, 2, (void*)DIR1, (void*)NULL); 
	init_action(&test.t_cleanup_actions[0], NOSLEEP, RMDIR, 2, (void*)DIR1, (void*)NULL);
	execute_test(&test);

	/* exchangedata is not supported on APFS volumes */
	if (!path_on_apfs(PDIR)) {
		init_test(&test, "4.1.7: exchangedata", FILE1, 2, 2, NOTE_ATTRIB, YES_EVENT);
		init_action(&(test.t_prep_actions[0]), NOSLEEP, CREAT, 2, (void*)FILE1, (void*)NULL);
		init_action(&(test.t_prep_actions[1]), NOSLEEP, CREAT, 2, (void*)FILE2, (void*)NULL);
		init_action(&test.t_helpthreadact, SLEEP, EXCHANGEDATA, 2, (void*)FILE1, (void*)FILE2); 
		init_action(&test.t_cleanup_actions[0], NOSLEEP, UNLINK, 2, (void*)FILE1, (void*)NULL);
		init_action(&test.t_cleanup_actions[1], NOSLEEP, UNLINK, 2, (void*)FILE2, (void*)NULL);
		execute_test(&test);
	}

	init_test(&test, "4.1.8: utimes on a file", FILE1, 1, 1, NOTE_ATTRIB, YES_EVENT);
	test.t_nondeterministic = 1;
	init_action(&(test.t_prep_actions[0]), NOSLEEP, CREAT, 2, (void*)FILE1, (void*)NULL);
	init_action(&test.t_helpthreadact, SLEEP, UTIMES, 2, (void*)FILE1, (void*)NULL); 
	init_action(&test.t_cleanup_actions[0], NOSLEEP, UNLINK, 2, (void*)FILE1, (void*)NULL);
	execute_test(&test);
	
	init_test(&test, "4.1.9: utimes on a dir", DIR1, 1, 1, NOTE_ATTRIB, YES_EVENT);
	init_action(&(test.t_prep_actions[0]), NOSLEEP, MKDIR, 2, (void*)DIR1, (void*)NULL);
	init_action(&test.t_helpthreadact, SLEEP, UTIMES, 2, (void*)DIR1, (void*)NULL); 
	init_action(&test.t_cleanup_actions[0], NOSLEEP, RMDIR, 2, (void*)DIR1, (void*)NULL);
	execute_test(&test);
	
	
	/* ====== NO EVENT TESTS ========== */
	
	init_test(&test, "4.2.1: rename a file", FILE1, 1, 1, NOTE_ATTRIB, NO_EVENT);
	init_action(&(test.t_prep_actions[0]), NOSLEEP, CREAT, 2, (void*)FILE1, (void*)NULL);
	init_action(&test.t_helpthreadact, SLEEP, RENAME, 2, (void*)FILE1, (void*)FILE2);
	init_action(&test.t_cleanup_actions[0], NOSLEEP, UNLINK, 2, (void*)FILE2, NULL);
	execute_test(&test);
	
	init_test(&test, "4.2.2: open (do not change) a file", FILE1, 1, 1, NOTE_ATTRIB, NO_EVENT);
	init_action(&(test.t_prep_actions[0]), NOSLEEP, CREAT, 2, (void*)FILE1, (void*)NULL);
	init_action(&test.t_helpthreadact, SLEEP, OPEN, 2, (void*)FILE1, NULL);
	init_action(&test.t_cleanup_actions[0], NOSLEEP, UNLINK, 2, (void*)FILE1, NULL);
	execute_test(&test);
	
	init_test(&test, "4.2.3: stat a file", FILE1, 1, 1, NOTE_ATTRIB, NO_EVENT);
	init_action(&(test.t_prep_actions[0]), NOSLEEP, CREAT, 2, (void*)FILE1, (void*)NULL);
	init_action(&test.t_helpthreadact, SLEEP, STAT, 2, (void*)FILE1, NULL);
	init_action(&test.t_cleanup_actions[0], NOSLEEP, UNLINK, 2, (void*)FILE1, NULL);
	execute_test(&test);
	
	init_test(&test, "4.2.4: unlink a file", FILE1, 1, 0, NOTE_ATTRIB, NO_EVENT);
	init_action(&(test.t_prep_actions[0]), NOSLEEP, CREAT, 2, (void*)FILE1, (void*)NULL);
	init_action(&test.t_helpthreadact, SLEEP, UNLINK, 2, (void*)FILE1, NULL);
	execute_test(&test);
	
	init_test(&test, "4.2.5: write to a file", FILE1, 1, 1, NOTE_ATTRIB, NO_EVENT);
	init_action(&(test.t_prep_actions[0]), NOSLEEP, CREAT, 2, (void*)FILE1, (void*)NULL);
	init_action(&test.t_helpthreadact, SLEEP, WRITE, 2, (void*)FILE1, (void*)NULL); 
	init_action(&test.t_cleanup_actions[0], NOSLEEP, UNLINK, 2, (void*)FILE1, (void*)NULL);
	execute_test(&test);
	
	T_LOG("EXPECT SPURIOUS NOTE_ATTRIB EVENTS FROM DIRECTORY OPERATIONS on HFS.\n");
	init_test(&test, "4.2.6: add a file to a directory with creat()", DIR1, 1, 2, NOTE_ATTRIB, NO_EVENT);
	test.t_known_failure = 1;
	makepath(pathbuf, DIR1, FILE1);
	init_action(&(test.t_prep_actions[0]), NOSLEEP, MKDIR, 2, (void*)DIR1, (void*)NULL);
	init_action(&test.t_helpthreadact, SLEEP, CREAT, 2, (void*)pathbuf, (void*)NULL); 
	init_action(&test.t_cleanup_actions[0], NOSLEEP, UNLINK, 2, (void*)pathbuf, (void*)NULL);
	init_action(&test.t_cleanup_actions[1], NOSLEEP, RMDIR, 2, (void*)DIR1, (void*)NULL);
	execute_test(&test);
	
	init_test(&test, "4.2.7: mkdir in a dir", DIR1, 1, 2, NOTE_ATTRIB, NO_EVENT);
	test.t_known_failure = 1;
	makepath(pathbuf, DIR1, DIR2);
	init_action(&(test.t_prep_actions[0]), NOSLEEP, MKDIR, 2, (void*)DIR1, (void*)NULL);
	init_action(&test.t_helpthreadact, SLEEP, MKDIR, 2, (void*)pathbuf, (void*)NULL); 
	init_action(&test.t_cleanup_actions[0], NOSLEEP, RMDIR, 2, (void*)pathbuf, (void*)NULL);
	init_action(&test.t_cleanup_actions[1], NOSLEEP, RMDIR, 2, (void*)DIR1, (void*)NULL);
	execute_test(&test);
	
	init_test(&test, "4.2.8: add a symlink to a directory", DIR1, 1, 2, NOTE_ATTRIB, NO_EVENT);
	test.t_known_failure = 1;
	makepath(pathbuf, DIR1, FILE1);
	init_action(&(test.t_prep_actions[0]), NOSLEEP, MKDIR, 2, (void*)DIR1, (void*)NULL);
	init_action(&test.t_helpthreadact, SLEEP, SYMLINK, 2, (void*)DOTDOT, (void*)pathbuf); 
	init_action(&test.t_cleanup_actions[0], NOSLEEP, UNLINK, 2, (void*)pathbuf, (void*)NULL);
	init_action(&test.t_cleanup_actions[1], NOSLEEP, RMDIR, 2, (void*)DIR1, (void*)NULL);
	execute_test(&test);
	
	init_test(&test, "4.2.9: rename into a dir()", DIR1, 2, 2, NOTE_ATTRIB, NO_EVENT);
	test.t_known_failure = 1;
	makepath(pathbuf, DIR1, FILE1);
	init_action(&(test.t_prep_actions[0]), NOSLEEP, MKDIR, 2, (void*)DIR1, (void*)NULL);
	init_action(&(test.t_prep_actions[1]), NOSLEEP, CREAT, 2, (void*)FILE1, (void*)NULL);
	init_action(&test.t_helpthreadact, SLEEP, RENAME, 2, (void*)FILE1, (void*)pathbuf); 
	init_action(&test.t_cleanup_actions[0], NOSLEEP, UNLINK, 2, (void*)pathbuf, (void*)NULL);
	init_action(&test.t_cleanup_actions[1], NOSLEEP, RMDIR, 2, (void*)DIR1, (void*)NULL);
	execute_test(&test);
	
	init_test(&test, "4.2.10: unlink() file from dir", DIR1, 2, 1, NOTE_ATTRIB, NO_EVENT);
	test.t_known_failure = 1;
	makepath(pathbuf, DIR1, FILE1);
	init_action(&(test.t_prep_actions[0]), NOSLEEP, MKDIR, 2, (void*)DIR1, (void*)NULL);
	init_action(&(test.t_prep_actions[1]), NOSLEEP, CREAT, 2, (void*)pathbuf, (void*)NULL);
	init_action(&test.t_helpthreadact, SLEEP, UNLINK, 2, (void*)pathbuf, (void*)NULL); 
	init_action(&test.t_cleanup_actions[0], NOSLEEP, RMDIR, 2, (void*)DIR1, (void*)NULL);
	execute_test(&test);
	
	init_test(&test, "4.2.11: mkfifo in a directory", DIR1, 1, 2, NOTE_ATTRIB, NO_EVENT);
	test.t_known_failure = 1;
	makepath(pathbuf, DIR1, FILE1);
	init_action(&(test.t_prep_actions[0]), NOSLEEP, MKDIR, 2, (void*)DIR1, (void*)NULL);
	init_action(&test.t_helpthreadact, SLEEP, MKFIFO, 1, (void*)pathbuf); 
	init_action(&test.t_cleanup_actions[0], NOSLEEP, UNLINK, 2, (void*)pathbuf, (void*)NULL);
	init_action(&test.t_cleanup_actions[1], NOSLEEP, RMDIR, 2, (void*)DIR1, (void*)NULL);
	execute_test(&test);
	
	
}