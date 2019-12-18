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
struct bfa_itnim_iostats_s {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfa_fcpim_add_iostats (struct bfa_itnim_iostats_s*,struct bfa_itnim_iostats_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_comps ; 
 int /*<<< orphan*/  create_comps ; 
 int /*<<< orphan*/  creates ; 
 int /*<<< orphan*/  delete_comps ; 
 int /*<<< orphan*/  deletes ; 
 int /*<<< orphan*/  fw_create ; 
 int /*<<< orphan*/  fw_delete ; 
 int /*<<< orphan*/  input_reqs ; 
 int /*<<< orphan*/  io_aborts ; 
 int /*<<< orphan*/  io_cleanups ; 
 int /*<<< orphan*/  io_comps ; 
 int /*<<< orphan*/  io_tmaborts ; 
 int /*<<< orphan*/  ioc_disabled ; 
 int /*<<< orphan*/  iocom_dif_err ; 
 int /*<<< orphan*/  iocom_hostabrts ; 
 int /*<<< orphan*/  iocom_nexus_abort ; 
 int /*<<< orphan*/  iocom_proto_err ; 
 int /*<<< orphan*/  iocom_res_free ; 
 int /*<<< orphan*/  iocom_sqer_needed ; 
 int /*<<< orphan*/  iocom_utags ; 
 int /*<<< orphan*/  iocomp_aborted ; 
 int /*<<< orphan*/  iocomp_ok ; 
 int /*<<< orphan*/  iocomp_overrun ; 
 int /*<<< orphan*/  iocomp_timedout ; 
 int /*<<< orphan*/  iocomp_underrun ; 
 int /*<<< orphan*/  no_iotags ; 
 int /*<<< orphan*/  no_tskims ; 
 int /*<<< orphan*/  offlines ; 
 int /*<<< orphan*/  onlines ; 
 int /*<<< orphan*/  output_reqs ; 
 int /*<<< orphan*/  qresumes ; 
 int /*<<< orphan*/  rd_throughput ; 
 int /*<<< orphan*/  sler_events ; 
 int /*<<< orphan*/  tm_cleanup_comps ; 
 int /*<<< orphan*/  tm_cleanups ; 
 int /*<<< orphan*/  tm_cmnds ; 
 int /*<<< orphan*/  tm_failures ; 
 int /*<<< orphan*/  tm_fw_rsps ; 
 int /*<<< orphan*/  tm_io_comps ; 
 int /*<<< orphan*/  tm_iocdowns ; 
 int /*<<< orphan*/  tm_qresumes ; 
 int /*<<< orphan*/  tm_success ; 
 int /*<<< orphan*/  total_ios ; 
 int /*<<< orphan*/  wr_throughput ; 

void
bfa_fcpim_add_stats(struct bfa_itnim_iostats_s *lstats,
		struct bfa_itnim_iostats_s *rstats)
{
	bfa_fcpim_add_iostats(lstats, rstats, total_ios);
	bfa_fcpim_add_iostats(lstats, rstats, qresumes);
	bfa_fcpim_add_iostats(lstats, rstats, no_iotags);
	bfa_fcpim_add_iostats(lstats, rstats, io_aborts);
	bfa_fcpim_add_iostats(lstats, rstats, no_tskims);
	bfa_fcpim_add_iostats(lstats, rstats, iocomp_ok);
	bfa_fcpim_add_iostats(lstats, rstats, iocomp_underrun);
	bfa_fcpim_add_iostats(lstats, rstats, iocomp_overrun);
	bfa_fcpim_add_iostats(lstats, rstats, iocomp_aborted);
	bfa_fcpim_add_iostats(lstats, rstats, iocomp_timedout);
	bfa_fcpim_add_iostats(lstats, rstats, iocom_nexus_abort);
	bfa_fcpim_add_iostats(lstats, rstats, iocom_proto_err);
	bfa_fcpim_add_iostats(lstats, rstats, iocom_dif_err);
	bfa_fcpim_add_iostats(lstats, rstats, iocom_sqer_needed);
	bfa_fcpim_add_iostats(lstats, rstats, iocom_res_free);
	bfa_fcpim_add_iostats(lstats, rstats, iocom_hostabrts);
	bfa_fcpim_add_iostats(lstats, rstats, iocom_utags);
	bfa_fcpim_add_iostats(lstats, rstats, io_cleanups);
	bfa_fcpim_add_iostats(lstats, rstats, io_tmaborts);
	bfa_fcpim_add_iostats(lstats, rstats, onlines);
	bfa_fcpim_add_iostats(lstats, rstats, offlines);
	bfa_fcpim_add_iostats(lstats, rstats, creates);
	bfa_fcpim_add_iostats(lstats, rstats, deletes);
	bfa_fcpim_add_iostats(lstats, rstats, create_comps);
	bfa_fcpim_add_iostats(lstats, rstats, delete_comps);
	bfa_fcpim_add_iostats(lstats, rstats, sler_events);
	bfa_fcpim_add_iostats(lstats, rstats, fw_create);
	bfa_fcpim_add_iostats(lstats, rstats, fw_delete);
	bfa_fcpim_add_iostats(lstats, rstats, ioc_disabled);
	bfa_fcpim_add_iostats(lstats, rstats, cleanup_comps);
	bfa_fcpim_add_iostats(lstats, rstats, tm_cmnds);
	bfa_fcpim_add_iostats(lstats, rstats, tm_fw_rsps);
	bfa_fcpim_add_iostats(lstats, rstats, tm_success);
	bfa_fcpim_add_iostats(lstats, rstats, tm_failures);
	bfa_fcpim_add_iostats(lstats, rstats, tm_io_comps);
	bfa_fcpim_add_iostats(lstats, rstats, tm_qresumes);
	bfa_fcpim_add_iostats(lstats, rstats, tm_iocdowns);
	bfa_fcpim_add_iostats(lstats, rstats, tm_cleanups);
	bfa_fcpim_add_iostats(lstats, rstats, tm_cleanup_comps);
	bfa_fcpim_add_iostats(lstats, rstats, io_comps);
	bfa_fcpim_add_iostats(lstats, rstats, input_reqs);
	bfa_fcpim_add_iostats(lstats, rstats, output_reqs);
	bfa_fcpim_add_iostats(lstats, rstats, rd_throughput);
	bfa_fcpim_add_iostats(lstats, rstats, wr_throughput);
}