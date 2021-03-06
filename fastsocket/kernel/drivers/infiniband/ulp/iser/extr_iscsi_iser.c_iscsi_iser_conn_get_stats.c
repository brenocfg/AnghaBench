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
struct iscsi_stats {int custom_length; TYPE_1__* custom; int /*<<< orphan*/  tmfrsp_pdus; int /*<<< orphan*/  tmfcmd_pdus; int /*<<< orphan*/  r2t_pdus; int /*<<< orphan*/  datain_pdus; int /*<<< orphan*/  scsirsp_pdus; int /*<<< orphan*/  dataout_pdus; int /*<<< orphan*/  scsicmd_pdus; int /*<<< orphan*/  rxdata_octets; int /*<<< orphan*/  txdata_octets; } ;
struct iscsi_conn {int /*<<< orphan*/  fmr_unalign_cnt; int /*<<< orphan*/  eh_abort_cnt; int /*<<< orphan*/  tmfrsp_pdus_cnt; int /*<<< orphan*/  tmfcmd_pdus_cnt; int /*<<< orphan*/  r2t_pdus_cnt; int /*<<< orphan*/  datain_pdus_cnt; int /*<<< orphan*/  scsirsp_pdus_cnt; int /*<<< orphan*/  dataout_pdus_cnt; int /*<<< orphan*/  scsicmd_pdus_cnt; int /*<<< orphan*/  rxdata_octets; int /*<<< orphan*/  txdata_octets; } ;
struct iscsi_cls_conn {struct iscsi_conn* dd_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  value; int /*<<< orphan*/  desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
iscsi_iser_conn_get_stats(struct iscsi_cls_conn *cls_conn, struct iscsi_stats *stats)
{
	struct iscsi_conn *conn = cls_conn->dd_data;

	stats->txdata_octets = conn->txdata_octets;
	stats->rxdata_octets = conn->rxdata_octets;
	stats->scsicmd_pdus = conn->scsicmd_pdus_cnt;
	stats->dataout_pdus = conn->dataout_pdus_cnt;
	stats->scsirsp_pdus = conn->scsirsp_pdus_cnt;
	stats->datain_pdus = conn->datain_pdus_cnt; /* always 0 */
	stats->r2t_pdus = conn->r2t_pdus_cnt; /* always 0 */
	stats->tmfcmd_pdus = conn->tmfcmd_pdus_cnt;
	stats->tmfrsp_pdus = conn->tmfrsp_pdus_cnt;
	stats->custom_length = 4;
	strcpy(stats->custom[0].desc, "qp_tx_queue_full");
	stats->custom[0].value = 0; /* TB iser_conn->qp_tx_queue_full; */
	strcpy(stats->custom[1].desc, "fmr_map_not_avail");
	stats->custom[1].value = 0; /* TB iser_conn->fmr_map_not_avail */;
	strcpy(stats->custom[2].desc, "eh_abort_cnt");
	stats->custom[2].value = conn->eh_abort_cnt;
	strcpy(stats->custom[3].desc, "fmr_unalign_cnt");
	stats->custom[3].value = conn->fmr_unalign_cnt;
}