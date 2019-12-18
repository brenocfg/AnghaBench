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
struct TYPE_3__ {int /*<<< orphan*/  rx_flush; } ;
struct TYPE_4__ {TYPE_1__ btc_aa_snk_cb; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_EVENT (char*,int /*<<< orphan*/ ) ; 
 TYPE_2__ a2dp_sink_local_param ; 

void btc_a2dp_sink_set_rx_flush(BOOLEAN enable)
{
    APPL_TRACE_EVENT("## DROP RX %d ##\n", enable);
    a2dp_sink_local_param.btc_aa_snk_cb.rx_flush = enable;
}