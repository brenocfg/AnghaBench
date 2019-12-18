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
struct iscsi_stats {TYPE_1__* custom; scalar_t__ custom_length; scalar_t__ timeout_err; scalar_t__ digest_err; int /*<<< orphan*/  r2t_pdus; int /*<<< orphan*/  tmfcmd_pdus; int /*<<< orphan*/  tmfrsp_pdus; int /*<<< orphan*/  datain_pdus; int /*<<< orphan*/  scsicmd_pdus; int /*<<< orphan*/  scsirsp_pdus; int /*<<< orphan*/  dataout_pdus; int /*<<< orphan*/  rxdata_octets; int /*<<< orphan*/  txdata_octets; } ;
struct iscsi_conn {int /*<<< orphan*/  eh_abort_cnt; int /*<<< orphan*/  r2t_pdus_cnt; int /*<<< orphan*/  tmfcmd_pdus_cnt; int /*<<< orphan*/  tmfrsp_pdus_cnt; int /*<<< orphan*/  datain_pdus_cnt; int /*<<< orphan*/  scsicmd_pdus_cnt; int /*<<< orphan*/  scsirsp_pdus_cnt; int /*<<< orphan*/  dataout_pdus_cnt; int /*<<< orphan*/  rxdata_octets; int /*<<< orphan*/  txdata_octets; scalar_t__ dd_data; } ;
struct iscsi_cls_conn {struct iscsi_conn* dd_data; } ;
struct beiscsi_hba {int dummy; } ;
struct beiscsi_conn {struct beiscsi_hba* phba; } ;
struct TYPE_2__ {int /*<<< orphan*/  value; int /*<<< orphan*/  desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEISCSI_LOG_CONFIG ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

void beiscsi_conn_get_stats(struct iscsi_cls_conn *cls_conn,
			    struct iscsi_stats *stats)
{
	struct iscsi_conn *conn = cls_conn->dd_data;
	struct beiscsi_hba *phba = NULL;

	phba = ((struct beiscsi_conn *)conn->dd_data)->phba;
	beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_CONFIG,
		    "BS_%d : In beiscsi_conn_get_stats\n");

	stats->txdata_octets = conn->txdata_octets;
	stats->rxdata_octets = conn->rxdata_octets;
	stats->dataout_pdus = conn->dataout_pdus_cnt;
	stats->scsirsp_pdus = conn->scsirsp_pdus_cnt;
	stats->scsicmd_pdus = conn->scsicmd_pdus_cnt;
	stats->datain_pdus = conn->datain_pdus_cnt;
	stats->tmfrsp_pdus = conn->tmfrsp_pdus_cnt;
	stats->tmfcmd_pdus = conn->tmfcmd_pdus_cnt;
	stats->r2t_pdus = conn->r2t_pdus_cnt;
	stats->digest_err = 0;
	stats->timeout_err = 0;
	stats->custom_length = 0;
	strcpy(stats->custom[0].desc, "eh_abort_cnt");
	stats->custom[0].value = conn->eh_abort_cnt;
}