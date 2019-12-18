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
struct TYPE_2__ {scalar_t__ seq_release; scalar_t__ seq_assign; scalar_t__ seq_exch_abort; scalar_t__ exch_mgr_reset; scalar_t__ exch_done; scalar_t__ seq_els_rsp_send; scalar_t__ seq_send; scalar_t__ exch_seq_send; scalar_t__ seq_set_resp; scalar_t__ seq_start_next; } ;
struct fc_lport {TYPE_1__ tt; } ;

/* Variables and functions */
 scalar_t__ fc_exch_done ; 
 scalar_t__ fc_exch_mgr_reset ; 
 scalar_t__ fc_exch_seq_send ; 
 scalar_t__ fc_seq_assign ; 
 scalar_t__ fc_seq_els_rsp_send ; 
 scalar_t__ fc_seq_exch_abort ; 
 scalar_t__ fc_seq_release ; 
 scalar_t__ fc_seq_send ; 
 scalar_t__ fc_seq_set_resp ; 
 scalar_t__ fc_seq_start_next ; 

int fc_exch_init(struct fc_lport *lport)
{
	if (!lport->tt.seq_start_next)
		lport->tt.seq_start_next = fc_seq_start_next;

	if (!lport->tt.seq_set_resp)
		lport->tt.seq_set_resp = fc_seq_set_resp;

	if (!lport->tt.exch_seq_send)
		lport->tt.exch_seq_send = fc_exch_seq_send;

	if (!lport->tt.seq_send)
		lport->tt.seq_send = fc_seq_send;

	if (!lport->tt.seq_els_rsp_send)
		lport->tt.seq_els_rsp_send = fc_seq_els_rsp_send;

	if (!lport->tt.exch_done)
		lport->tt.exch_done = fc_exch_done;

	if (!lport->tt.exch_mgr_reset)
		lport->tt.exch_mgr_reset = fc_exch_mgr_reset;

	if (!lport->tt.seq_exch_abort)
		lport->tt.seq_exch_abort = fc_seq_exch_abort;

	if (!lport->tt.seq_assign)
		lport->tt.seq_assign = fc_seq_assign;

	if (!lport->tt.seq_release)
		lport->tt.seq_release = fc_seq_release;

	return 0;
}