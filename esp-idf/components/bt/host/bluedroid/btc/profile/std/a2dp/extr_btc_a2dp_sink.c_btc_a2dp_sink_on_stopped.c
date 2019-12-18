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
typedef  int /*<<< orphan*/  tBTA_AV_SUSPEND ;
struct TYPE_3__ {int /*<<< orphan*/  rx_flush; } ;
struct TYPE_4__ {TYPE_1__ btc_aa_snk_cb; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_2__ a2dp_sink_local_param ; 
 int /*<<< orphan*/  btc_a2dp_control_set_datachnl_stat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btc_a2dp_sink_rx_flush_req () ; 

void btc_a2dp_sink_on_stopped(tBTA_AV_SUSPEND *p_av)
{
    a2dp_sink_local_param.btc_aa_snk_cb.rx_flush = TRUE;
    btc_a2dp_sink_rx_flush_req();
    btc_a2dp_control_set_datachnl_stat(FALSE);
}