#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_storage {int dummy; } ;
struct sockaddr {int dummy; } ;
struct qla_conn {TYPE_1__* qla_ep; } ;
struct iscsi_conn {struct qla_conn* dd_data; } ;
struct iscsi_cls_conn {struct iscsi_conn* dd_data; } ;
typedef  enum iscsi_param { ____Placeholder_iscsi_param } iscsi_param ;
struct TYPE_2__ {int /*<<< orphan*/  dst_addr; } ;

/* Variables and functions */
#define  ISCSI_PARAM_CONN_ADDRESS 129 
#define  ISCSI_PARAM_CONN_PORT 128 
 int iscsi_conn_get_addr_param (struct sockaddr_storage*,int,char*) ; 
 int iscsi_conn_get_param (struct iscsi_cls_conn*,int,char*) ; 

__attribute__((used)) static int qla4xxx_conn_get_param(struct iscsi_cls_conn *cls_conn,
				  enum iscsi_param param, char *buf)
{
	struct iscsi_conn *conn;
	struct qla_conn *qla_conn;
	struct sockaddr *dst_addr;
	int len = 0;

	conn = cls_conn->dd_data;
	qla_conn = conn->dd_data;
	dst_addr = (struct sockaddr *)&qla_conn->qla_ep->dst_addr;

	switch (param) {
	case ISCSI_PARAM_CONN_PORT:
	case ISCSI_PARAM_CONN_ADDRESS:
		return iscsi_conn_get_addr_param((struct sockaddr_storage *)
						 dst_addr, param, buf);
	default:
		return iscsi_conn_get_param(cls_conn, param, buf);
	}

	return len;

}