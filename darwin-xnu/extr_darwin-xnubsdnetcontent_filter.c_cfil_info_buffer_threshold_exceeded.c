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
struct TYPE_4__ {scalar_t__ cfi_tail_drop_cnt; } ;
struct TYPE_3__ {scalar_t__ cfi_tail_drop_cnt; } ;
struct cfil_info {TYPE_2__ cfi_rcv; TYPE_1__ cfi_snd; } ;

/* Variables and functions */

bool
cfil_info_buffer_threshold_exceeded(struct cfil_info *cfil_info)
{
	if (cfil_info == NULL)
		return false;

	/*
	 * Clean up flow if it exceeded queue thresholds
	 */
	if (cfil_info->cfi_snd.cfi_tail_drop_cnt ||
		cfil_info->cfi_rcv.cfi_tail_drop_cnt) {
#if GC_DEBUG
		CFIL_LOG(LOG_ERR, "CFIL: queue threshold exceeded: mbuf max <count: %d bytes: %d> tail drop count <OUT: %d IN: %d>",
				 cfil_udp_gc_mbuf_num_max,
				 cfil_udp_gc_mbuf_cnt_max,
				 cfil_info->cfi_snd.cfi_tail_drop_cnt,
				 cfil_info->cfi_rcv.cfi_tail_drop_cnt);
		cfil_info_log(LOG_ERR, cfil_info, "CFIL: queue threshold exceeded");
#endif
		return true;
	}

	return false;
}