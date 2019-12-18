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
struct cmtp_session {int /*<<< orphan*/  num; int /*<<< orphan*/  state; int /*<<< orphan*/  flags; int /*<<< orphan*/  bdaddr; } ;
struct cmtp_conninfo {int /*<<< orphan*/  num; int /*<<< orphan*/  state; int /*<<< orphan*/  flags; int /*<<< orphan*/  bdaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  bacpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __cmtp_copy_session(struct cmtp_session *session, struct cmtp_conninfo *ci)
{
	bacpy(&ci->bdaddr, &session->bdaddr);

	ci->flags = session->flags;
	ci->state = session->state;

	ci->num = session->num;
}