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
struct TYPE_2__ {int /*<<< orphan*/  btc_aa_snk_task_hdl; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSI_THREAD_MAX_TIMEOUT ; 
 TYPE_1__ a2dp_sink_local_param ; 
 int /*<<< orphan*/  btc_a2dp_sink_data_ready ; 
 int /*<<< orphan*/  osi_thread_post (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void btc_a2dp_sink_data_post(void)
{
    osi_thread_post(a2dp_sink_local_param.btc_aa_snk_task_hdl, btc_a2dp_sink_data_ready, NULL, 1, OSI_THREAD_MAX_TIMEOUT);
}