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
struct TYPE_3__ {int /*<<< orphan*/  RxSbcQ; } ;
struct TYPE_4__ {TYPE_1__ btc_aa_snk_cb; } ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_DEBUG (char*) ; 
 TYPE_2__ a2dp_sink_local_param ; 
 int /*<<< orphan*/  btc_a2dp_sink_flush_q (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void btc_a2dp_sink_rx_flush(void)
{
    /* Flush all enqueued SBC  buffers (encoded) */
    APPL_TRACE_DEBUG("btc_a2dp_sink_rx_flush");

    btc_a2dp_sink_flush_q(a2dp_sink_local_param.btc_aa_snk_cb.RxSbcQ);
}