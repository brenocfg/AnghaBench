#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct iscsi_tcp_conn {struct cxgbi_conn* dd_data; } ;
struct iscsi_conn {int /*<<< orphan*/  datadgst_en; int /*<<< orphan*/  hdrdgst_en; struct iscsi_tcp_conn* dd_data; } ;
struct iscsi_cls_conn {struct iscsi_conn* dd_data; } ;
struct cxgbi_sock {int /*<<< orphan*/  tid; TYPE_2__* cdev; } ;
struct cxgbi_conn {TYPE_1__* cep; } ;
typedef  enum iscsi_param { ____Placeholder_iscsi_param } iscsi_param ;
struct TYPE_4__ {int (* csk_ddp_setup_digest ) (struct cxgbi_sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {struct cxgbi_sock* csk; } ;

/* Variables and functions */
 int CXGBI_DBG_ISCSI ; 
#define  ISCSI_PARAM_DATADGST_EN 132 
#define  ISCSI_PARAM_HDRDGST_EN 131 
#define  ISCSI_PARAM_MAX_R2T 130 
#define  ISCSI_PARAM_MAX_RECV_DLENGTH 129 
#define  ISCSI_PARAM_MAX_XMIT_DLENGTH 128 
 int cxgbi_conn_max_recv_dlength (struct iscsi_conn*) ; 
 int cxgbi_conn_max_xmit_dlength (struct iscsi_conn*) ; 
 int iscsi_set_param (struct iscsi_cls_conn*,int,char*,int) ; 
 int iscsi_tcp_set_max_r2t (struct iscsi_conn*,char*) ; 
 int /*<<< orphan*/  log_debug (int,char*,struct iscsi_cls_conn*,int,int,char*) ; 
 int stub1 (struct cxgbi_sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub2 (struct cxgbi_sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int cxgbi_set_conn_param(struct iscsi_cls_conn *cls_conn,
			enum iscsi_param param, char *buf, int buflen)
{
	struct iscsi_conn *conn = cls_conn->dd_data;
	struct iscsi_tcp_conn *tcp_conn = conn->dd_data;
	struct cxgbi_conn *cconn = tcp_conn->dd_data;
	struct cxgbi_sock *csk = cconn->cep->csk;
	int err;

	log_debug(1 << CXGBI_DBG_ISCSI,
		"cls_conn 0x%p, param %d, buf(%d) %s.\n",
		cls_conn, param, buflen, buf);

	switch (param) {
	case ISCSI_PARAM_HDRDGST_EN:
		err = iscsi_set_param(cls_conn, param, buf, buflen);
		if (!err && conn->hdrdgst_en)
			err = csk->cdev->csk_ddp_setup_digest(csk, csk->tid,
							conn->hdrdgst_en,
							conn->datadgst_en, 0);
		break;
	case ISCSI_PARAM_DATADGST_EN:
		err = iscsi_set_param(cls_conn, param, buf, buflen);
		if (!err && conn->datadgst_en)
			err = csk->cdev->csk_ddp_setup_digest(csk, csk->tid,
							conn->hdrdgst_en,
							conn->datadgst_en, 0);
		break;
	case ISCSI_PARAM_MAX_R2T:
		return iscsi_tcp_set_max_r2t(conn, buf);
	case ISCSI_PARAM_MAX_RECV_DLENGTH:
		err = iscsi_set_param(cls_conn, param, buf, buflen);
		if (!err)
			err = cxgbi_conn_max_recv_dlength(conn);
		break;
	case ISCSI_PARAM_MAX_XMIT_DLENGTH:
		err = iscsi_set_param(cls_conn, param, buf, buflen);
		if (!err)
			err = cxgbi_conn_max_xmit_dlength(conn);
		break;
	default:
		return iscsi_set_param(cls_conn, param, buf, buflen);
	}
	return err;
}