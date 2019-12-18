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
typedef  int /*<<< orphan*/  uint64_t ;
struct mptses {int mpte_svctype; int mpte_flags; scalar_t__ mpte_triggered_cell; scalar_t__ mpte_used_wifi; scalar_t__ mpte_handshake_success; int /*<<< orphan*/  mpte_used_cell; scalar_t__ mpte_initial_cell; } ;
typedef  scalar_t__ boolean_t ;
struct TYPE_2__ {int /*<<< orphan*/  tcps_mptcp_triggered_cell; int /*<<< orphan*/  tcps_mptcp_back_to_wifi; int /*<<< orphan*/  tcps_mptcp_aggregate_all_bytes; int /*<<< orphan*/  tcps_mptcp_aggregate_cell_bytes; int /*<<< orphan*/  tcps_mptcp_aggregate_success; int /*<<< orphan*/  tcps_mptcp_aggregate_attempt; int /*<<< orphan*/  tcps_mptcp_fp_aggregate_success; int /*<<< orphan*/  tcps_mptcp_fp_aggregate_attempt; int /*<<< orphan*/  tcps_mptcp_interactive_all_bytes; int /*<<< orphan*/  tcps_mptcp_interactive_cell_bytes; int /*<<< orphan*/  tcps_mptcp_interactive_cell_from_wifi; int /*<<< orphan*/  tcps_mptcp_interactive_success; int /*<<< orphan*/  tcps_mptcp_interactive_attempt; int /*<<< orphan*/  tcps_mptcp_fp_interactive_success; int /*<<< orphan*/  tcps_mptcp_fp_interactive_attempt; int /*<<< orphan*/  tcps_mptcp_handover_all_bytes; int /*<<< orphan*/  tcps_mptcp_handover_cell_bytes; int /*<<< orphan*/  tcps_mptcp_handover_cell_from_wifi; int /*<<< orphan*/  tcps_mptcp_handover_success_wifi; int /*<<< orphan*/  tcps_mptcp_handover_wifi_from_cell; int /*<<< orphan*/  tcps_mptcp_handover_success_cell; int /*<<< orphan*/  tcps_mptcp_handover_attempt; int /*<<< orphan*/  tcps_mptcp_fp_handover_success_wifi; int /*<<< orphan*/  tcps_mptcp_fp_handover_success_cell; int /*<<< orphan*/  tcps_mptcp_fp_handover_attempt; } ;

/* Variables and functions */
#define  MPTCP_SVCTYPE_AGGREGATE 130 
#define  MPTCP_SVCTYPE_HANDOVER 129 
#define  MPTCP_SVCTYPE_INTERACTIVE 128 
 int MPTE_FIRSTPARTY ; 
 int /*<<< orphan*/  mptcpstats_get_bytes (struct mptses*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__ tcpstat ; 

__attribute__((used)) static void
mptcpstats_session_wrapup(struct mptses *mpte)
{
	boolean_t cell = mpte->mpte_initial_cell;

	switch (mpte->mpte_svctype) {
	case MPTCP_SVCTYPE_HANDOVER:
		if (mpte->mpte_flags & MPTE_FIRSTPARTY) {
			tcpstat.tcps_mptcp_fp_handover_attempt++;

			if (cell && mpte->mpte_handshake_success) {
				tcpstat.tcps_mptcp_fp_handover_success_cell++;

				if (mpte->mpte_used_wifi)
					tcpstat.tcps_mptcp_handover_wifi_from_cell++;
			} else if (mpte->mpte_handshake_success) {
				tcpstat.tcps_mptcp_fp_handover_success_wifi++;

				if (mpte->mpte_used_cell)
					tcpstat.tcps_mptcp_handover_cell_from_wifi++;
			}
		} else {
			tcpstat.tcps_mptcp_handover_attempt++;

			if (cell && mpte->mpte_handshake_success) {
				tcpstat.tcps_mptcp_handover_success_cell++;

				if (mpte->mpte_used_wifi)
					tcpstat.tcps_mptcp_handover_wifi_from_cell++;
			} else if (mpte->mpte_handshake_success) {
				tcpstat.tcps_mptcp_handover_success_wifi++;

				if (mpte->mpte_used_cell)
					tcpstat.tcps_mptcp_handover_cell_from_wifi++;
			}
		}

		if (mpte->mpte_handshake_success) {
			uint64_t cellbytes;
			uint64_t allbytes;

			mptcpstats_get_bytes(mpte, cell, &cellbytes, &allbytes);

			tcpstat.tcps_mptcp_handover_cell_bytes += cellbytes;
			tcpstat.tcps_mptcp_handover_all_bytes += allbytes;
		}
		break;
	case MPTCP_SVCTYPE_INTERACTIVE:
		if (mpte->mpte_flags & MPTE_FIRSTPARTY) {
			tcpstat.tcps_mptcp_fp_interactive_attempt++;

			if (mpte->mpte_handshake_success) {
				tcpstat.tcps_mptcp_fp_interactive_success++;

				if (!cell && mpte->mpte_used_cell)
					tcpstat.tcps_mptcp_interactive_cell_from_wifi++;
			}
		} else {
			tcpstat.tcps_mptcp_interactive_attempt++;

			if (mpte->mpte_handshake_success) {
				tcpstat.tcps_mptcp_interactive_success++;

				if (!cell && mpte->mpte_used_cell)
					tcpstat.tcps_mptcp_interactive_cell_from_wifi++;
			}
		}

		if (mpte->mpte_handshake_success) {
			uint64_t cellbytes;
			uint64_t allbytes;

			mptcpstats_get_bytes(mpte, cell, &cellbytes, &allbytes);

			tcpstat.tcps_mptcp_interactive_cell_bytes += cellbytes;
			tcpstat.tcps_mptcp_interactive_all_bytes += allbytes;
		}
		break;
	case MPTCP_SVCTYPE_AGGREGATE:
		if (mpte->mpte_flags & MPTE_FIRSTPARTY) {
			tcpstat.tcps_mptcp_fp_aggregate_attempt++;

			if (mpte->mpte_handshake_success)
				tcpstat.tcps_mptcp_fp_aggregate_success++;
		} else {
			tcpstat.tcps_mptcp_aggregate_attempt++;

			if (mpte->mpte_handshake_success) {
				tcpstat.tcps_mptcp_aggregate_success++;
			}
		}

		if (mpte->mpte_handshake_success) {
			uint64_t cellbytes;
			uint64_t allbytes;

			mptcpstats_get_bytes(mpte, cell, &cellbytes, &allbytes);

			tcpstat.tcps_mptcp_aggregate_cell_bytes += cellbytes;
			tcpstat.tcps_mptcp_aggregate_all_bytes += allbytes;
		}
		break;
	}

	if (cell && mpte->mpte_handshake_success && mpte->mpte_used_wifi)
		tcpstat.tcps_mptcp_back_to_wifi++;

	if (mpte->mpte_triggered_cell)
		tcpstat.tcps_mptcp_triggered_cell++;
}