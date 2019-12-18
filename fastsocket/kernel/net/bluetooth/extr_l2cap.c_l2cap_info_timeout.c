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
struct l2cap_conn {scalar_t__ info_ident; int /*<<< orphan*/  info_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  L2CAP_INFO_FEAT_MASK_REQ_DONE ; 
 int /*<<< orphan*/  l2cap_conn_start (struct l2cap_conn*) ; 

__attribute__((used)) static void l2cap_info_timeout(unsigned long arg)
{
	struct l2cap_conn *conn = (void *) arg;

	conn->info_state |= L2CAP_INFO_FEAT_MASK_REQ_DONE;
	conn->info_ident = 0;

	l2cap_conn_start(conn);
}