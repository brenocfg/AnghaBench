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
struct TYPE_4__ {int /*<<< orphan*/  t_helpthreadact; int /*<<< orphan*/ * t_prep_actions; int /*<<< orphan*/ * t_cleanup_actions; } ;
typedef  TYPE_1__ test_t ;

/* Variables and functions */
 int /*<<< orphan*/  CREAT ; 
 scalar_t__ FILE1 ; 
 int /*<<< orphan*/  NOSLEEP ; 
 int /*<<< orphan*/  NOTE_REVOKE ; 
 int /*<<< orphan*/  NO_EVENT ; 
 int /*<<< orphan*/  REVOKE ; 
 int /*<<< orphan*/  SLEEP ; 
 int /*<<< orphan*/  UNLINK ; 
 int /*<<< orphan*/  YES_EVENT ; 
 int /*<<< orphan*/  execute_test (TYPE_1__*) ; 
 int /*<<< orphan*/  init_action (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void*) ; 
 int /*<<< orphan*/  init_test (TYPE_1__*,char*,scalar_t__,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void 
run_note_revoke_tests() 
{
	test_t test;
	init_test(&test, "7.1.1: revoke file", FILE1, 1, 1, NOTE_REVOKE, YES_EVENT);
	init_action(&(test.t_prep_actions[0]), NOSLEEP, CREAT, 1, (void*)FILE1);
	init_action(&test.t_helpthreadact, SLEEP, REVOKE, 1, (void*)FILE1);
	init_action(&(test.t_cleanup_actions[0]), NOSLEEP, UNLINK, 1, (void*)FILE1);
	execute_test(&test);
	
	init_test(&test, "7.2.1: delete file", FILE1, 1, 0, NOTE_REVOKE, NO_EVENT);
	init_action(&(test.t_prep_actions[0]), NOSLEEP, CREAT, 1, (void*)FILE1);
	init_action(&test.t_helpthreadact, SLEEP, UNLINK, 1, (void*)FILE1);
	execute_test(&test);
}