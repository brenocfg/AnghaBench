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
struct TYPE_6__ {int /*<<< orphan*/  entries; int /*<<< orphan*/  index; } ;
struct efx_tx_queue {int queue; TYPE_3__ txd; TYPE_1__* channel; struct efx_nic* efx; } ;
struct efx_nic {TYPE_2__* type; } ;
typedef  int /*<<< orphan*/  efx_oword_t ;
struct TYPE_5__ {int /*<<< orphan*/  txd_ptr_tbl_base; } ;
struct TYPE_4__ {int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int EFX_MAX_TX_QUEUES ; 
 int /*<<< orphan*/  EFX_POPULATE_OWORD_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EFX_POPULATE_OWORD_10 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ EFX_REV_FALCON_B0 ; 
 int /*<<< orphan*/  EFX_SET_OWORD_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int EFX_TXQ_TYPE_HIGHPRI ; 
 int EFX_TXQ_TYPE_OFFLOAD ; 
 int /*<<< orphan*/  FFE_BZ_TX_PACE_OFF ; 
 int /*<<< orphan*/  FFE_BZ_TX_PACE_RESERVED ; 
 int /*<<< orphan*/  FRF_AZ_TX_DESCQ_BUF_BASE_ID ; 
 int /*<<< orphan*/  FRF_AZ_TX_DESCQ_EN ; 
 int /*<<< orphan*/  FRF_AZ_TX_DESCQ_EVQ_ID ; 
 int /*<<< orphan*/  FRF_AZ_TX_DESCQ_LABEL ; 
 int /*<<< orphan*/  FRF_AZ_TX_DESCQ_OWNER_ID ; 
 int /*<<< orphan*/  FRF_AZ_TX_DESCQ_SIZE ; 
 int /*<<< orphan*/  FRF_AZ_TX_DESCQ_TYPE ; 
 int /*<<< orphan*/  FRF_AZ_TX_ISCSI_DDIG_EN ; 
 int /*<<< orphan*/  FRF_AZ_TX_ISCSI_HDIG_EN ; 
 int /*<<< orphan*/  FRF_BZ_TX_IP_CHKSM_DIS ; 
 int /*<<< orphan*/  FRF_BZ_TX_NON_IP_DROP_DIS ; 
 int /*<<< orphan*/  FRF_BZ_TX_PACE ; 
 int /*<<< orphan*/  FRF_BZ_TX_TCP_CHKSM_DIS ; 
 int /*<<< orphan*/  FR_AA_TX_CHKSM_CFG ; 
 int /*<<< orphan*/  FR_BZ_TX_PACE_TBL ; 
 int /*<<< orphan*/  __clear_bit_le (int,void*) ; 
 int /*<<< orphan*/  __ffs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_bit_le (int,void*) ; 
 int /*<<< orphan*/  efx_init_special_buffer (struct efx_nic*,TYPE_3__*) ; 
 scalar_t__ efx_nic_rev (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_reado (struct efx_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_writeo (struct efx_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_writeo_table (struct efx_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void efx_nic_init_tx(struct efx_tx_queue *tx_queue)
{
	struct efx_nic *efx = tx_queue->efx;
	efx_oword_t reg;

	/* Pin TX descriptor ring */
	efx_init_special_buffer(efx, &tx_queue->txd);

	/* Push TX descriptor ring to card */
	EFX_POPULATE_OWORD_10(reg,
			      FRF_AZ_TX_DESCQ_EN, 1,
			      FRF_AZ_TX_ISCSI_DDIG_EN, 0,
			      FRF_AZ_TX_ISCSI_HDIG_EN, 0,
			      FRF_AZ_TX_DESCQ_BUF_BASE_ID, tx_queue->txd.index,
			      FRF_AZ_TX_DESCQ_EVQ_ID,
			      tx_queue->channel->channel,
			      FRF_AZ_TX_DESCQ_OWNER_ID, 0,
			      FRF_AZ_TX_DESCQ_LABEL, tx_queue->queue,
			      FRF_AZ_TX_DESCQ_SIZE,
			      __ffs(tx_queue->txd.entries),
			      FRF_AZ_TX_DESCQ_TYPE, 0,
			      FRF_BZ_TX_NON_IP_DROP_DIS, 1);

	if (efx_nic_rev(efx) >= EFX_REV_FALCON_B0) {
		int csum = tx_queue->queue & EFX_TXQ_TYPE_OFFLOAD;
		EFX_SET_OWORD_FIELD(reg, FRF_BZ_TX_IP_CHKSM_DIS, !csum);
		EFX_SET_OWORD_FIELD(reg, FRF_BZ_TX_TCP_CHKSM_DIS,
				    !csum);
	}

	efx_writeo_table(efx, &reg, efx->type->txd_ptr_tbl_base,
			 tx_queue->queue);

	if (efx_nic_rev(efx) < EFX_REV_FALCON_B0) {
		/* Only 128 bits in this register */
		BUILD_BUG_ON(EFX_MAX_TX_QUEUES > 128);

		efx_reado(efx, &reg, FR_AA_TX_CHKSM_CFG);
		if (tx_queue->queue & EFX_TXQ_TYPE_OFFLOAD)
			__clear_bit_le(tx_queue->queue, (void *)&reg);
		else
			__set_bit_le(tx_queue->queue, (void *)&reg);
		efx_writeo(efx, &reg, FR_AA_TX_CHKSM_CFG);
	}

	if (efx_nic_rev(efx) >= EFX_REV_FALCON_B0) {
		EFX_POPULATE_OWORD_1(reg,
				     FRF_BZ_TX_PACE,
				     (tx_queue->queue & EFX_TXQ_TYPE_HIGHPRI) ?
				     FFE_BZ_TX_PACE_OFF :
				     FFE_BZ_TX_PACE_RESERVED);
		efx_writeo_table(efx, &reg, FR_BZ_TX_PACE_TBL,
				 tx_queue->queue);
	}
}