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
struct t3cdev {int dummy; } ;
struct cxgbi_device {int flags; int nports; int skb_rx_extra; int /*<<< orphan*/ * ports; TYPE_2__** hbas; int /*<<< orphan*/ * itp; int /*<<< orphan*/  dev_ddp_cleanup; int /*<<< orphan*/  skb_tx_rsvd; int /*<<< orphan*/  rx_credit_thres; int /*<<< orphan*/  rcv_win; int /*<<< orphan*/  snd_win; int /*<<< orphan*/  nmtus; int /*<<< orphan*/  mtus; int /*<<< orphan*/  pdev; struct t3cdev* lldev; } ;
struct cpl_iscsi_hdr_norss {int dummy; } ;
struct TYPE_3__ {int nports; int /*<<< orphan*/  mtus; } ;
struct adapter {TYPE_1__ params; int /*<<< orphan*/ * port; int /*<<< orphan*/  pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  ipv4addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CXGB3I_MAX_LUN ; 
 int /*<<< orphan*/  CXGB3I_TX_HEADER_LEN ; 
 int CXGBI_FLAG_DEV_T3 ; 
 int CXGBI_FLAG_IPV4_SET ; 
 int /*<<< orphan*/  CXGBI_MAX_CONN ; 
 int /*<<< orphan*/  NMTUS ; 
 int cxgb3i_ddp_init (struct cxgbi_device*) ; 
 int /*<<< orphan*/  cxgb3i_get_private_ipv4addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxgb3i_host_template ; 
 int /*<<< orphan*/  cxgb3i_iscsi_transport ; 
 int cxgb3i_ofld_init (struct cxgbi_device*) ; 
 int /*<<< orphan*/  cxgb3i_rcv_win ; 
 int /*<<< orphan*/  cxgb3i_rx_credit_thres ; 
 int /*<<< orphan*/  cxgb3i_snd_win ; 
 int /*<<< orphan*/  cxgb3i_stt ; 
 struct cxgbi_device* cxgbi_device_find_by_lldev (struct t3cdev*) ; 
 struct cxgbi_device* cxgbi_device_register (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cxgbi_device_unregister (struct cxgbi_device*) ; 
 int cxgbi_hbas_add (struct cxgbi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,struct cxgbi_device*,...) ; 
 int /*<<< orphan*/  pr_warn (char*,struct t3cdev*) ; 
 int /*<<< orphan*/  t3_ddp_cleanup ; 
 struct adapter* tdev2adap (struct t3cdev*) ; 

__attribute__((used)) static void cxgb3i_dev_open(struct t3cdev *t3dev)
{
	struct cxgbi_device *cdev = cxgbi_device_find_by_lldev(t3dev);
	struct adapter *adapter = tdev2adap(t3dev);
	int i, err;

	if (cdev) {
		pr_info("0x%p, updating.\n", cdev);
		return;
	}

	cdev = cxgbi_device_register(0, adapter->params.nports);
	if (!cdev) {
		pr_warn("device 0x%p register failed.\n", t3dev);
		return;
	}

	cdev->flags = CXGBI_FLAG_DEV_T3 | CXGBI_FLAG_IPV4_SET;
	cdev->lldev = t3dev;
	cdev->pdev = adapter->pdev;
	cdev->ports = adapter->port;
	cdev->nports = adapter->params.nports;
	cdev->mtus = adapter->params.mtus;
	cdev->nmtus = NMTUS;
	cdev->snd_win = cxgb3i_snd_win;
	cdev->rcv_win = cxgb3i_rcv_win;
	cdev->rx_credit_thres = cxgb3i_rx_credit_thres;
	cdev->skb_tx_rsvd = CXGB3I_TX_HEADER_LEN;
	cdev->skb_rx_extra = sizeof(struct cpl_iscsi_hdr_norss);
	cdev->dev_ddp_cleanup = t3_ddp_cleanup;
	cdev->itp = &cxgb3i_iscsi_transport;

	err = cxgb3i_ddp_init(cdev);
	if (err) {
		pr_info("0x%p ddp init failed\n", cdev);
		goto err_out;
	}

	err = cxgb3i_ofld_init(cdev);
	if (err) {
		pr_info("0x%p offload init failed\n", cdev);
		goto err_out;
	}

	err = cxgbi_hbas_add(cdev, CXGB3I_MAX_LUN, CXGBI_MAX_CONN,
				&cxgb3i_host_template, cxgb3i_stt);
	if (err)
		goto err_out;

	for (i = 0; i < cdev->nports; i++)
		cdev->hbas[i]->ipv4addr =
			cxgb3i_get_private_ipv4addr(cdev->ports[i]);

	pr_info("cdev 0x%p, f 0x%x, t3dev 0x%p open, err %d.\n",
		cdev, cdev ? cdev->flags : 0, t3dev, err);
	return;

err_out:
	cxgbi_device_unregister(cdev);
}