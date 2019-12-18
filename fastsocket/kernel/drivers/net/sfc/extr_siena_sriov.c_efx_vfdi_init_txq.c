#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned int index; unsigned int evq; unsigned int buf_count; unsigned int label; int /*<<< orphan*/  addr; } ;
struct TYPE_6__ {TYPE_2__ init_txq; } ;
struct vfdi_req {TYPE_3__ u; } ;
struct TYPE_4__ {struct vfdi_req* addr; } ;
struct efx_vf {scalar_t__ tx_filter_mode; int /*<<< orphan*/  txq_lock; int /*<<< orphan*/  txq_count; int /*<<< orphan*/  txq_mask; int /*<<< orphan*/  pci_name; TYPE_1__ buf; struct efx_nic* efx; } ;
struct efx_nic {int /*<<< orphan*/  vi_scale; int /*<<< orphan*/  net_dev; } ;
typedef  int /*<<< orphan*/  efx_oword_t ;

/* Variables and functions */
 unsigned int EFX_BUFTBL_TXQ_BASE (struct efx_vf*,unsigned int) ; 
 unsigned int EFX_FIELD_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EFX_MAX_DMAQ_SIZE ; 
 int /*<<< orphan*/  EFX_POPULATE_OWORD_8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FRF_AZ_TX_DESCQ_BUF_BASE_ID ; 
 int /*<<< orphan*/  FRF_AZ_TX_DESCQ_EN ; 
 int /*<<< orphan*/  FRF_AZ_TX_DESCQ_EVQ_ID ; 
 int /*<<< orphan*/  FRF_AZ_TX_DESCQ_LABEL ; 
 int /*<<< orphan*/  FRF_AZ_TX_DESCQ_SIZE ; 
 int /*<<< orphan*/  FRF_BZ_TX_NON_IP_DROP_DIS ; 
 int /*<<< orphan*/  FRF_CZ_TX_DPT_ETH_FILT_EN ; 
 int /*<<< orphan*/  FRF_CZ_TX_DPT_Q_MASK_WIDTH ; 
 int /*<<< orphan*/  FR_BZ_TX_DESC_PTR_TBL ; 
 int VFDI_RC_EINVAL ; 
 int VFDI_RC_SUCCESS ; 
 scalar_t__ VF_TX_FILTER_ON ; 
 int /*<<< orphan*/  __ffs (unsigned int) ; 
 scalar_t__ __test_and_set_bit (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abs_index (struct efx_vf*,unsigned int) ; 
 scalar_t__ bad_buf_count (unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ bad_vf_index (struct efx_nic*,unsigned int) ; 
 int /*<<< orphan*/  efx_sriov_bufs (struct efx_nic*,unsigned int,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  efx_writeo_table (struct efx_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ net_ratelimit () ; 
 int /*<<< orphan*/  netif_err (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int) ; 
 unsigned int vf_max_tx_channels ; 

__attribute__((used)) static int efx_vfdi_init_txq(struct efx_vf *vf)
{
	struct efx_nic *efx = vf->efx;
	struct vfdi_req *req = vf->buf.addr;
	unsigned vf_txq = req->u.init_txq.index;
	unsigned vf_evq = req->u.init_txq.evq;
	unsigned buf_count = req->u.init_txq.buf_count;
	unsigned buftbl = EFX_BUFTBL_TXQ_BASE(vf, vf_txq);
	unsigned label, eth_filt_en;
	efx_oword_t reg;

	if (bad_vf_index(efx, vf_evq) || bad_vf_index(efx, vf_txq) ||
	    vf_txq >= vf_max_tx_channels ||
	    bad_buf_count(buf_count, EFX_MAX_DMAQ_SIZE)) {
		if (net_ratelimit())
			netif_err(efx, hw, efx->net_dev,
				  "ERROR: Invalid INIT_TXQ from %s: txq %d evq %d "
				  "buf_count %d\n", vf->pci_name, vf_txq,
				  vf_evq, buf_count);
		return VFDI_RC_EINVAL;
	}

	mutex_lock(&vf->txq_lock);
	if (__test_and_set_bit(req->u.init_txq.index, vf->txq_mask))
		++vf->txq_count;
	mutex_unlock(&vf->txq_lock);
	efx_sriov_bufs(efx, buftbl, req->u.init_txq.addr, buf_count);

	eth_filt_en = vf->tx_filter_mode == VF_TX_FILTER_ON;

	label = req->u.init_txq.label & EFX_FIELD_MASK(FRF_AZ_TX_DESCQ_LABEL);
	EFX_POPULATE_OWORD_8(reg,
			     FRF_CZ_TX_DPT_Q_MASK_WIDTH, min(efx->vi_scale, 1U),
			     FRF_CZ_TX_DPT_ETH_FILT_EN, eth_filt_en,
			     FRF_AZ_TX_DESCQ_EN, 1,
			     FRF_AZ_TX_DESCQ_BUF_BASE_ID, buftbl,
			     FRF_AZ_TX_DESCQ_EVQ_ID, abs_index(vf, vf_evq),
			     FRF_AZ_TX_DESCQ_LABEL, label,
			     FRF_AZ_TX_DESCQ_SIZE, __ffs(buf_count),
			     FRF_BZ_TX_NON_IP_DROP_DIS, 1);
	efx_writeo_table(efx, &reg, FR_BZ_TX_DESC_PTR_TBL,
			 abs_index(vf, vf_txq));

	return VFDI_RC_SUCCESS;
}