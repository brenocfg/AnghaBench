#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned long prb_con; int avg_con; int new_con; int use_pcnt; } ;
union cvmx_ipd_red_quex_param {scalar_t__ u64; TYPE_2__ s; } ;
struct TYPE_3__ {int drop; int pass; } ;
union cvmx_ipd_qosx_red_marks {TYPE_1__ s; scalar_t__ u64; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_IPD_QOSX_RED_MARKS (int) ; 
 int /*<<< orphan*/  CVMX_IPD_RED_QUEX_PARAM (int) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,scalar_t__) ; 

int cvmx_helper_setup_red_queue(int queue, int pass_thresh, int drop_thresh)
{
	union cvmx_ipd_qosx_red_marks red_marks;
	union cvmx_ipd_red_quex_param red_param;

	/* Set RED to begin dropping packets when there are pass_thresh buffers
	   left. It will linearly drop more packets until reaching drop_thresh
	   buffers */
	red_marks.u64 = 0;
	red_marks.s.drop = drop_thresh;
	red_marks.s.pass = pass_thresh;
	cvmx_write_csr(CVMX_IPD_QOSX_RED_MARKS(queue), red_marks.u64);

	/* Use the actual queue 0 counter, not the average */
	red_param.u64 = 0;
	red_param.s.prb_con =
	    (255ul << 24) / (red_marks.s.pass - red_marks.s.drop);
	red_param.s.avg_con = 1;
	red_param.s.new_con = 255;
	red_param.s.use_pcnt = 1;
	cvmx_write_csr(CVMX_IPD_RED_QUEX_PARAM(queue), red_param.u64);
	return 0;
}