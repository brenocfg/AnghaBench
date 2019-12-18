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
struct bnep_session {int dummy; } ;
struct bnep_conninfo {int /*<<< orphan*/  dst; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  __bnep_copy_ci (struct bnep_conninfo*,struct bnep_session*) ; 
 struct bnep_session* __bnep_get_session (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnep_session_sem ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

int bnep_get_conninfo(struct bnep_conninfo *ci)
{
	struct bnep_session *s;
	int err = 0;

	down_read(&bnep_session_sem);

	s = __bnep_get_session(ci->dst);
	if (s)
		__bnep_copy_ci(ci, s);
	else
		err = -ENOENT;

	up_read(&bnep_session_sem);
	return err;
}