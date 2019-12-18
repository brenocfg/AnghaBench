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
typedef  int /*<<< orphan*/  uint32_t ;
struct iscsi_iser_conn {struct iscsi_conn* iscsi_conn; } ;
struct iscsi_conn {struct iscsi_iser_conn* dd_data; int /*<<< orphan*/  max_recv_dlength; } ;
struct iscsi_cls_session {int dummy; } ;
struct iscsi_cls_conn {struct iscsi_conn* dd_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISER_RECV_DATA_SEG_LEN ; 
 struct iscsi_cls_conn* iscsi_conn_setup (struct iscsi_cls_session*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct iscsi_cls_conn *
iscsi_iser_conn_create(struct iscsi_cls_session *cls_session, uint32_t conn_idx)
{
	struct iscsi_conn *conn;
	struct iscsi_cls_conn *cls_conn;
	struct iscsi_iser_conn *iser_conn;

	cls_conn = iscsi_conn_setup(cls_session, sizeof(*iser_conn), conn_idx);
	if (!cls_conn)
		return NULL;
	conn = cls_conn->dd_data;

	/*
	 * due to issues with the login code re iser sematics
	 * this not set in iscsi_conn_setup - FIXME
	 */
	conn->max_recv_dlength = ISER_RECV_DATA_SEG_LEN;

	iser_conn = conn->dd_data;
	conn->dd_data = iser_conn;
	iser_conn->iscsi_conn = conn;

	return cls_conn;
}