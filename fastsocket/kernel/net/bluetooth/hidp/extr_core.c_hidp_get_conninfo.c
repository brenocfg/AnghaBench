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
struct hidp_session {int dummy; } ;
struct hidp_conninfo {int /*<<< orphan*/  bdaddr; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  __hidp_copy_session (struct hidp_session*,struct hidp_conninfo*) ; 
 struct hidp_session* __hidp_get_session (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hidp_session_sem ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

int hidp_get_conninfo(struct hidp_conninfo *ci)
{
	struct hidp_session *session;
	int err = 0;

	down_read(&hidp_session_sem);

	session = __hidp_get_session(&ci->bdaddr);
	if (session)
		__hidp_copy_session(session, ci);
	else
		err = -ENOENT;

	up_read(&hidp_session_sem);
	return err;
}