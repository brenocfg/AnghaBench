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
struct sockaddr_storage {int dummy; } ;
struct iscsi_endpoint {struct cxgbi_endpoint* dd_data; } ;
struct cxgbi_sock {int /*<<< orphan*/  daddr; } ;
struct cxgbi_endpoint {struct cxgbi_sock* csk; } ;
typedef  enum iscsi_param { ____Placeholder_iscsi_param } iscsi_param ;

/* Variables and functions */
 int CXGBI_DBG_ISCSI ; 
 int ENOSYS ; 
 int ENOTCONN ; 
#define  ISCSI_PARAM_CONN_ADDRESS 129 
#define  ISCSI_PARAM_CONN_PORT 128 
 int iscsi_conn_get_addr_param (struct sockaddr_storage*,int,char*) ; 
 int /*<<< orphan*/  log_debug (int,char*,struct iscsi_endpoint*,int) ; 

int cxgbi_get_ep_param(struct iscsi_endpoint *ep, enum iscsi_param param,
		       char *buf)
{
	struct cxgbi_endpoint *cep = ep->dd_data;
	struct cxgbi_sock *csk;
	int len;

	log_debug(1 << CXGBI_DBG_ISCSI,
		"cls_conn 0x%p, param %d.\n", ep, param);

	switch (param) {
	case ISCSI_PARAM_CONN_PORT:
	case ISCSI_PARAM_CONN_ADDRESS:
		if (!cep)
			return -ENOTCONN;

		csk = cep->csk;
		if (!csk)
			return -ENOTCONN;

		return iscsi_conn_get_addr_param((struct sockaddr_storage *)
						 &csk->daddr, param, buf);
	default:
		return -ENOSYS;
	}
	return len;
}