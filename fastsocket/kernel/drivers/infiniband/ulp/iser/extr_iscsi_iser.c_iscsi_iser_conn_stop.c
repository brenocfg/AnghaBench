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
struct iser_conn {int dummy; } ;
struct iscsi_iser_conn {struct iser_conn* ib_conn; } ;
struct iscsi_conn {struct iscsi_iser_conn* dd_data; } ;
struct iscsi_cls_conn {struct iscsi_conn* dd_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  iscsi_conn_stop (struct iscsi_cls_conn*,int) ; 
 int /*<<< orphan*/  iser_conn_put (struct iser_conn*,int) ; 

__attribute__((used)) static void
iscsi_iser_conn_stop(struct iscsi_cls_conn *cls_conn, int flag)
{
	struct iscsi_conn *conn = cls_conn->dd_data;
	struct iscsi_iser_conn *iser_conn = conn->dd_data;
	struct iser_conn *ib_conn = iser_conn->ib_conn;

	/*
	 * Userspace may have goofed up and not bound the connection or
	 * might have only partially setup the connection.
	 */
	if (ib_conn) {
		iscsi_conn_stop(cls_conn, flag);
		/*
		 * There is no unbind event so the stop callback
		 * must release the ref from the bind.
		 */
		iser_conn_put(ib_conn, 1); /* deref iscsi/ib conn unbinding */
	}
	iser_conn->ib_conn = NULL;
}