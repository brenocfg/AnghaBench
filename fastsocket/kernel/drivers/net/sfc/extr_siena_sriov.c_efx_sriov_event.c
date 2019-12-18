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
typedef  int u64 ;
struct efx_vf {int busy; unsigned int req_type; unsigned int req_seqno; int req_addr; int /*<<< orphan*/  pci_name; int /*<<< orphan*/  req; } ;
struct efx_nic {int /*<<< orphan*/  net_dev; } ;
struct efx_channel {struct efx_nic* efx; } ;
typedef  int /*<<< orphan*/  efx_qword_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 unsigned int EFX_QWORD_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ FSF_CZ_USER_EV_REG_VALUE_LBN ; 
 int /*<<< orphan*/  FSF_CZ_USER_QID ; 
 int /*<<< orphan*/  VFDI_EV_DATA ; 
 int /*<<< orphan*/  VFDI_EV_SEQ ; 
 int /*<<< orphan*/  VFDI_EV_TYPE ; 
#define  VFDI_EV_TYPE_REQ_WORD0 131 
#define  VFDI_EV_TYPE_REQ_WORD1 130 
#define  VFDI_EV_TYPE_REQ_WORD2 129 
#define  VFDI_EV_TYPE_REQ_WORD3 128 
 int /*<<< orphan*/  hw ; 
 scalar_t__ map_vi_index (struct efx_nic*,unsigned int,struct efx_vf**,int /*<<< orphan*/ *) ; 
 scalar_t__ net_ratelimit () ; 
 int /*<<< orphan*/  netif_err (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_vdbg (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfdi_workqueue ; 

void efx_sriov_event(struct efx_channel *channel, efx_qword_t *event)
{
	struct efx_nic *efx = channel->efx;
	struct efx_vf *vf;
	unsigned qid, seq, type, data;

	qid = EFX_QWORD_FIELD(*event, FSF_CZ_USER_QID);

	/* USR_EV_REG_VALUE is dword0, so access the VFDI_EV fields directly */
	BUILD_BUG_ON(FSF_CZ_USER_EV_REG_VALUE_LBN != 0);
	seq = EFX_QWORD_FIELD(*event, VFDI_EV_SEQ);
	type = EFX_QWORD_FIELD(*event, VFDI_EV_TYPE);
	data = EFX_QWORD_FIELD(*event, VFDI_EV_DATA);

	netif_vdbg(efx, hw, efx->net_dev,
		   "USR_EV event from qid %d seq 0x%x type %d data 0x%x\n",
		   qid, seq, type, data);

	if (map_vi_index(efx, qid, &vf, NULL))
		return;
	if (vf->busy)
		goto error;

	if (type == VFDI_EV_TYPE_REQ_WORD0) {
		/* Resynchronise */
		vf->req_type = VFDI_EV_TYPE_REQ_WORD0;
		vf->req_seqno = seq + 1;
		vf->req_addr = 0;
	} else if (seq != (vf->req_seqno++ & 0xff) || type != vf->req_type)
		goto error;

	switch (vf->req_type) {
	case VFDI_EV_TYPE_REQ_WORD0:
	case VFDI_EV_TYPE_REQ_WORD1:
	case VFDI_EV_TYPE_REQ_WORD2:
		vf->req_addr |= (u64)data << (vf->req_type << 4);
		++vf->req_type;
		return;

	case VFDI_EV_TYPE_REQ_WORD3:
		vf->req_addr |= (u64)data << 48;
		vf->req_type = VFDI_EV_TYPE_REQ_WORD0;
		vf->busy = true;
		queue_work(vfdi_workqueue, &vf->req);
		return;
	}

error:
	if (net_ratelimit())
		netif_err(efx, hw, efx->net_dev,
			  "ERROR: Screaming VFDI request from %s\n",
			  vf->pci_name);
	/* Reset the request and sequence number */
	vf->req_type = VFDI_EV_TYPE_REQ_WORD0;
	vf->req_seqno = seq + 1;
}