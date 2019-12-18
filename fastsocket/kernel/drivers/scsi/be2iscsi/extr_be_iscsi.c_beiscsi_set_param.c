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
struct iscsi_session {int first_burst; int max_burst; } ;
struct iscsi_conn {int max_recv_dlength; int max_xmit_dlength; scalar_t__ dd_data; struct iscsi_session* session; } ;
struct iscsi_cls_conn {struct iscsi_conn* dd_data; } ;
struct beiscsi_hba {int dummy; } ;
struct beiscsi_conn {struct beiscsi_hba* phba; } ;
typedef  enum iscsi_param { ____Placeholder_iscsi_param } iscsi_param ;

/* Variables and functions */
 int /*<<< orphan*/  BEISCSI_LOG_CONFIG ; 
#define  ISCSI_PARAM_FIRST_BURST 131 
#define  ISCSI_PARAM_MAX_BURST 130 
#define  ISCSI_PARAM_MAX_RECV_DLENGTH 129 
#define  ISCSI_PARAM_MAX_XMIT_DLENGTH 128 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int iscsi_set_param (struct iscsi_cls_conn*,int,char*,int) ; 

int beiscsi_set_param(struct iscsi_cls_conn *cls_conn,
		      enum iscsi_param param, char *buf, int buflen)
{
	struct iscsi_conn *conn = cls_conn->dd_data;
	struct iscsi_session *session = conn->session;
	struct beiscsi_hba *phba = NULL;
	int ret;

	phba = ((struct beiscsi_conn *)conn->dd_data)->phba;
	beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_CONFIG,
		    "BS_%d : In beiscsi_conn_set_param,"
		    " param= %d\n", param);

	ret = iscsi_set_param(cls_conn, param, buf, buflen);
	if (ret)
		return ret;
	/*
	 * If userspace tried to set the value to higher than we can
	 * support override here.
	 */
	switch (param) {
	case ISCSI_PARAM_FIRST_BURST:
		if (session->first_burst > 8192)
			session->first_burst = 8192;
		break;
	case ISCSI_PARAM_MAX_RECV_DLENGTH:
		if (conn->max_recv_dlength > 65536)
			conn->max_recv_dlength = 65536;
		break;
	case ISCSI_PARAM_MAX_BURST:
		if (session->max_burst > 262144)
			session->max_burst = 262144;
		break;
	case ISCSI_PARAM_MAX_XMIT_DLENGTH:
		if ((conn->max_xmit_dlength > 65536) ||
		    (conn->max_xmit_dlength == 0))
			conn->max_xmit_dlength = 65536;
	default:
		return 0;
	}

	return 0;
}