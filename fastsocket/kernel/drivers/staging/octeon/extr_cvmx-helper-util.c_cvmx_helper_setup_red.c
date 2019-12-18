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
struct TYPE_6__ {int prt_enb; int avg_dly; int prb_dly; } ;
union cvmx_ipd_red_port_enable {scalar_t__ u64; TYPE_3__ s; } ;
struct TYPE_4__ {int page_cnt; scalar_t__ bp_enb; } ;
union cvmx_ipd_portx_bp_page_cnt {scalar_t__ u64; TYPE_1__ s; } ;
struct TYPE_5__ {scalar_t__ prt_enb; } ;
union cvmx_ipd_bp_prt_red_end {scalar_t__ u64; TYPE_2__ s; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_IPD_BP_PRT_RED_END ; 
 int /*<<< orphan*/  CVMX_IPD_PORTX_BP_PAGE_CNT (int) ; 
 int /*<<< orphan*/  CVMX_IPD_RED_PORT_ENABLE ; 
 int cvmx_helper_get_first_ipd_port (int) ; 
 int cvmx_helper_get_last_ipd_port (int) ; 
 int /*<<< orphan*/  cvmx_helper_setup_red_queue (int,int,int) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,scalar_t__) ; 

int cvmx_helper_setup_red(int pass_thresh, int drop_thresh)
{
	union cvmx_ipd_portx_bp_page_cnt page_cnt;
	union cvmx_ipd_bp_prt_red_end ipd_bp_prt_red_end;
	union cvmx_ipd_red_port_enable red_port_enable;
	int queue;
	int interface;
	int port;

	/* Disable backpressure based on queued buffers. It needs SW support */
	page_cnt.u64 = 0;
	page_cnt.s.bp_enb = 0;
	page_cnt.s.page_cnt = 100;
	for (interface = 0; interface < 2; interface++) {
		for (port = cvmx_helper_get_first_ipd_port(interface);
		     port < cvmx_helper_get_last_ipd_port(interface); port++)
			cvmx_write_csr(CVMX_IPD_PORTX_BP_PAGE_CNT(port),
				       page_cnt.u64);
	}

	for (queue = 0; queue < 8; queue++)
		cvmx_helper_setup_red_queue(queue, pass_thresh, drop_thresh);

	/* Shutoff the dropping based on the per port page count. SW isn't
	   decrementing it right now */
	ipd_bp_prt_red_end.u64 = 0;
	ipd_bp_prt_red_end.s.prt_enb = 0;
	cvmx_write_csr(CVMX_IPD_BP_PRT_RED_END, ipd_bp_prt_red_end.u64);

	red_port_enable.u64 = 0;
	red_port_enable.s.prt_enb = 0xfffffffffull;
	red_port_enable.s.avg_dly = 10000;
	red_port_enable.s.prb_dly = 10000;
	cvmx_write_csr(CVMX_IPD_RED_PORT_ENABLE, red_port_enable.u64);

	return 0;
}