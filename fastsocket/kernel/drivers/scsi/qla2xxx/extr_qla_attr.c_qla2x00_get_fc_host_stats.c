#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct scsi_qla_host {int /*<<< orphan*/  loop_id; int /*<<< orphan*/  loop_state; } ;
struct qla_hw_data {int /*<<< orphan*/  s_dma_pool; int /*<<< orphan*/  dpc_active; int /*<<< orphan*/  pdev; } ;
struct link_statistics {int fcp_input_megabytes; int fcp_output_megabytes; int /*<<< orphan*/  nos_rcvd; int /*<<< orphan*/  nos_count; int /*<<< orphan*/  dumped_frames; int /*<<< orphan*/  rx_frames; int /*<<< orphan*/  tx_frames; int /*<<< orphan*/  lip_cnt; int /*<<< orphan*/  lip_count; int /*<<< orphan*/  inval_crc_cnt; int /*<<< orphan*/  invalid_crc_count; int /*<<< orphan*/  inval_xmit_word_cnt; int /*<<< orphan*/  invalid_tx_word_count; int /*<<< orphan*/  prim_seq_err_cnt; int /*<<< orphan*/  prim_seq_protocol_err_count; int /*<<< orphan*/  loss_sig_cnt; int /*<<< orphan*/  loss_of_signal_count; int /*<<< orphan*/  loss_sync_cnt; int /*<<< orphan*/  loss_of_sync_count; int /*<<< orphan*/  link_fail_cnt; int /*<<< orphan*/  link_failure_count; } ;
struct fc_host_statistics {int fcp_input_megabytes; int fcp_output_megabytes; int /*<<< orphan*/  nos_rcvd; int /*<<< orphan*/  nos_count; int /*<<< orphan*/  dumped_frames; int /*<<< orphan*/  rx_frames; int /*<<< orphan*/  tx_frames; int /*<<< orphan*/  lip_cnt; int /*<<< orphan*/  lip_count; int /*<<< orphan*/  inval_crc_cnt; int /*<<< orphan*/  invalid_crc_count; int /*<<< orphan*/  inval_xmit_word_cnt; int /*<<< orphan*/  invalid_tx_word_count; int /*<<< orphan*/  prim_seq_err_cnt; int /*<<< orphan*/  prim_seq_protocol_err_count; int /*<<< orphan*/  loss_sig_cnt; int /*<<< orphan*/  loss_of_signal_count; int /*<<< orphan*/  loss_sync_cnt; int /*<<< orphan*/  loss_of_sync_count; int /*<<< orphan*/  link_fail_cnt; int /*<<< orphan*/  link_failure_count; } ;
struct Scsi_Host {int dummy; } ;
struct TYPE_6__ {int input_bytes; int output_bytes; } ;
struct TYPE_7__ {TYPE_1__ qla_stats; int /*<<< orphan*/  dpc_flags; struct qla_hw_data* hw; struct link_statistics fc_host_stat; } ;
typedef  TYPE_2__ scsi_qla_host_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int DMA_POOL_SIZE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_FWI2_CAPABLE (struct qla_hw_data*) ; 
 scalar_t__ IS_QLAFX00 (struct qla_hw_data*) ; 
 scalar_t__ LOOP_READY ; 
 int QLA_FUNCTION_FAILED ; 
 int QLA_SUCCESS ; 
 int /*<<< orphan*/  UNLOADING ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 struct link_statistics* dma_pool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,struct link_statistics*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct link_statistics*,int,int) ; 
 int /*<<< orphan*/  pci_channel_offline (int /*<<< orphan*/ ) ; 
 struct scsi_qla_host* pci_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,TYPE_2__*,int,char*) ; 
 int /*<<< orphan*/  ql_log_warn ; 
 int qla24xx_get_isp_stats (struct scsi_qla_host*,struct link_statistics*,int /*<<< orphan*/ ) ; 
 int qla2x00_get_link_status (struct scsi_qla_host*,int /*<<< orphan*/ ,struct link_statistics*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla2x00_reset_active (TYPE_2__*) ; 
 TYPE_2__* shost_priv (struct Scsi_Host*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct fc_host_statistics *
qla2x00_get_fc_host_stats(struct Scsi_Host *shost)
{
	scsi_qla_host_t *vha = shost_priv(shost);
	struct qla_hw_data *ha = vha->hw;
	struct scsi_qla_host *base_vha = pci_get_drvdata(ha->pdev);
	int rval;
	struct link_statistics *stats;
	dma_addr_t stats_dma;
	struct fc_host_statistics *pfc_host_stat;

	pfc_host_stat = &vha->fc_host_stat;
	memset(pfc_host_stat, -1, sizeof(struct fc_host_statistics));

	if (IS_QLAFX00(vha->hw))
		goto done;

	if (test_bit(UNLOADING, &vha->dpc_flags))
		goto done;

	if (unlikely(pci_channel_offline(ha->pdev)))
		goto done;

	stats = dma_pool_alloc(ha->s_dma_pool, GFP_KERNEL, &stats_dma);
	if (stats == NULL) {
		ql_log(ql_log_warn, vha, 0x707d,
		    "Failed to allocate memory for stats.\n");
		goto done;
	}
	memset(stats, 0, DMA_POOL_SIZE);

	rval = QLA_FUNCTION_FAILED;
	if (IS_FWI2_CAPABLE(ha)) {
		rval = qla24xx_get_isp_stats(base_vha, stats, stats_dma);
	} else if (atomic_read(&base_vha->loop_state) == LOOP_READY &&
	    !qla2x00_reset_active(vha) && !ha->dpc_active) {
		/* Must be in a 'READY' state for statistics retrieval. */
		rval = qla2x00_get_link_status(base_vha, base_vha->loop_id,
						stats, stats_dma);
	}

	if (rval != QLA_SUCCESS)
		goto done_free;

	pfc_host_stat->link_failure_count = stats->link_fail_cnt;
	pfc_host_stat->loss_of_sync_count = stats->loss_sync_cnt;
	pfc_host_stat->loss_of_signal_count = stats->loss_sig_cnt;
	pfc_host_stat->prim_seq_protocol_err_count = stats->prim_seq_err_cnt;
	pfc_host_stat->invalid_tx_word_count = stats->inval_xmit_word_cnt;
	pfc_host_stat->invalid_crc_count = stats->inval_crc_cnt;
	if (IS_FWI2_CAPABLE(ha)) {
		pfc_host_stat->lip_count = stats->lip_cnt;
		pfc_host_stat->tx_frames = stats->tx_frames;
		pfc_host_stat->rx_frames = stats->rx_frames;
		pfc_host_stat->dumped_frames = stats->dumped_frames;
		pfc_host_stat->nos_count = stats->nos_rcvd;
	}
	pfc_host_stat->fcp_input_megabytes = vha->qla_stats.input_bytes >> 20;
	pfc_host_stat->fcp_output_megabytes = vha->qla_stats.output_bytes >> 20;

done_free:
        dma_pool_free(ha->s_dma_pool, stats, stats_dma);
done:
	return pfc_host_stat;
}