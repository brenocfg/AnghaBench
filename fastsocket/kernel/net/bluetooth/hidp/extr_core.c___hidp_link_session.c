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
struct hidp_session {int /*<<< orphan*/  conn; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  __module_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_conn_hold_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hidp_session_list ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __hidp_link_session(struct hidp_session *session)
{
	__module_get(THIS_MODULE);
	list_add(&session->list, &hidp_session_list);

	hci_conn_hold_device(session->conn);
}