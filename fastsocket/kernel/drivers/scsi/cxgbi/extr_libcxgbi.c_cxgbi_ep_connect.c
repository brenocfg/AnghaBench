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
struct sockaddr {int dummy; } ;
struct iscsi_endpoint {struct cxgbi_endpoint* dd_data; } ;
struct cxgbi_sock {size_t port_id; TYPE_1__* cdev; } ;
struct cxgbi_hba {TYPE_2__* ndev; } ;
struct cxgbi_endpoint {struct cxgbi_hba* chba; struct cxgbi_sock* csk; } ;
struct Scsi_Host {int /*<<< orphan*/  host_no; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int (* csk_init_act_open ) (struct cxgbi_sock*) ;struct cxgbi_hba** hbas; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTP_CONNECTING ; 
 int CXGBI_DBG_ISCSI ; 
 int CXGBI_DBG_SOCK ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ENOSPC ; 
 struct iscsi_endpoint* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct cxgbi_sock*) ; 
 struct cxgbi_sock* cxgbi_check_route (struct sockaddr*) ; 
 int /*<<< orphan*/  cxgbi_sock_closed (struct cxgbi_sock*) ; 
 int /*<<< orphan*/  cxgbi_sock_get (struct cxgbi_sock*) ; 
 scalar_t__ cxgbi_sock_is_closing (struct cxgbi_sock*) ; 
 int /*<<< orphan*/  cxgbi_sock_put (struct cxgbi_sock*) ; 
 int /*<<< orphan*/  cxgbi_sock_set_state (struct cxgbi_sock*,int /*<<< orphan*/ ) ; 
 struct iscsi_endpoint* iscsi_create_endpoint (int) ; 
 struct cxgbi_hba* iscsi_host_priv (struct Scsi_Host*) ; 
 int /*<<< orphan*/  log_debug (int,char*,...) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 int sock_get_port (struct cxgbi_sock*) ; 
 int stub1 (struct cxgbi_sock*) ; 

struct iscsi_endpoint *cxgbi_ep_connect(struct Scsi_Host *shost,
					struct sockaddr *dst_addr,
					int non_blocking)
{
	struct iscsi_endpoint *ep;
	struct cxgbi_endpoint *cep;
	struct cxgbi_hba *hba = NULL;
	struct cxgbi_sock *csk;
	int err = -EINVAL;

	log_debug(1 << CXGBI_DBG_ISCSI | 1 << CXGBI_DBG_SOCK,
		"shost 0x%p, non_blocking %d, dst_addr 0x%p.\n",
		shost, non_blocking, dst_addr);

	if (shost) {
		hba = iscsi_host_priv(shost);
		if (!hba) {
			pr_info("shost 0x%p, priv NULL.\n", shost);
			goto err_out;
		}
	}

	csk = cxgbi_check_route(dst_addr);
	if (IS_ERR(csk))
		return (struct iscsi_endpoint *)csk;
	cxgbi_sock_get(csk);

	if (!hba)
		hba = csk->cdev->hbas[csk->port_id];
	else if (hba != csk->cdev->hbas[csk->port_id]) {
		pr_info("Could not connect through requested host %u"
			"hba 0x%p != 0x%p (%u).\n",
			shost->host_no, hba,
			csk->cdev->hbas[csk->port_id], csk->port_id);
		err = -ENOSPC;
		goto release_conn;
	}

	err = sock_get_port(csk);
	if (err)
		goto release_conn;

	cxgbi_sock_set_state(csk, CTP_CONNECTING);
	err = csk->cdev->csk_init_act_open(csk);
	if (err)
		goto release_conn;

	if (cxgbi_sock_is_closing(csk)) {
		err = -ENOSPC;
		pr_info("csk 0x%p is closing.\n", csk);
		goto release_conn;
	}

	ep = iscsi_create_endpoint(sizeof(*cep));
	if (!ep) {
		err = -ENOMEM;
		pr_info("iscsi alloc ep, OOM.\n");
		goto release_conn;
	}

	cep = ep->dd_data;
	cep->csk = csk;
	cep->chba = hba;

	log_debug(1 << CXGBI_DBG_ISCSI | 1 << CXGBI_DBG_SOCK,
		"ep 0x%p, cep 0x%p, csk 0x%p, hba 0x%p,%s.\n",
		ep, cep, csk, hba, hba->ndev->name);
	return ep;

release_conn:
	cxgbi_sock_put(csk);
	cxgbi_sock_closed(csk);
err_out:
	return ERR_PTR(err);
}