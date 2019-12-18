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
struct iser_conn {int /*<<< orphan*/ * iser_conn; } ;
struct iscsi_iser_conn {struct iser_conn* ib_conn; } ;
struct iscsi_conn {struct iscsi_iser_conn* dd_data; } ;
struct iscsi_cls_conn {struct iscsi_conn* dd_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  iscsi_conn_teardown (struct iscsi_cls_conn*) ; 
 int /*<<< orphan*/  iser_conn_put (struct iser_conn*,int) ; 

__attribute__((used)) static void
iscsi_iser_conn_destroy(struct iscsi_cls_conn *cls_conn)
{
	struct iscsi_conn *conn = cls_conn->dd_data;
	struct iscsi_iser_conn *iser_conn = conn->dd_data;
	struct iser_conn *ib_conn = iser_conn->ib_conn;

	iscsi_conn_teardown(cls_conn);
	/*
	 * Userspace will normally call the stop callback and
	 * already have freed the ib_conn, but if it goofed up then
	 * we free it here.
	 */
	if (ib_conn) {
		ib_conn->iser_conn = NULL;
		iser_conn_put(ib_conn, 1); /* deref iscsi/ib conn unbinding */
	}
}