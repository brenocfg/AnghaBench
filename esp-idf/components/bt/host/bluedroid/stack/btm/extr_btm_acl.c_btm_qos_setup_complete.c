#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_9__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  delay_variation; int /*<<< orphan*/  latency; int /*<<< orphan*/  peak_bandwidth; int /*<<< orphan*/  token_rate; int /*<<< orphan*/  service_type; int /*<<< orphan*/  qos_flags; } ;
struct TYPE_12__ {TYPE_2__ flow; int /*<<< orphan*/  handle; int /*<<< orphan*/  status; } ;
typedef  TYPE_3__ tBTM_QOS_SETUP_CMPL ;
typedef  int /*<<< orphan*/  (* tBTM_CMPL_CB ) (TYPE_3__*) ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_10__ {int /*<<< orphan*/  (* p_qossu_cmpl_cb ) (TYPE_3__*) ;int /*<<< orphan*/  qossu_timer; } ;
struct TYPE_14__ {TYPE_1__ devcb; } ;
struct TYPE_13__ {int /*<<< orphan*/  delay_variation; int /*<<< orphan*/  latency; int /*<<< orphan*/  peak_bandwidth; int /*<<< orphan*/  token_rate; int /*<<< orphan*/  service_type; int /*<<< orphan*/  qos_flags; } ;
typedef  TYPE_5__ FLOW_SPEC ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_TRACE_DEBUG (char*,...) ; 
 TYPE_9__ btm_cb ; 
 int /*<<< orphan*/  btu_stop_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 

void btm_qos_setup_complete (UINT8 status, UINT16 handle, FLOW_SPEC *p_flow)
{
    tBTM_CMPL_CB            *p_cb = btm_cb.devcb.p_qossu_cmpl_cb;
    tBTM_QOS_SETUP_CMPL     qossu;
    BTM_TRACE_DEBUG ("btm_qos_setup_complete\n");
    btu_stop_timer (&btm_cb.devcb.qossu_timer);

    btm_cb.devcb.p_qossu_cmpl_cb = NULL;

    if (p_cb) {
        memset(&qossu, 0, sizeof(tBTM_QOS_SETUP_CMPL));
        qossu.status = status;
        qossu.handle = handle;
        if (p_flow != NULL) {
            qossu.flow.qos_flags = p_flow->qos_flags;
            qossu.flow.service_type = p_flow->service_type;
            qossu.flow.token_rate = p_flow->token_rate;
            qossu.flow.peak_bandwidth = p_flow->peak_bandwidth;
            qossu.flow.latency = p_flow->latency;
            qossu.flow.delay_variation = p_flow->delay_variation;
        }
        BTM_TRACE_DEBUG ("BTM: p_flow->delay_variation: 0x%02x\n",
                         qossu.flow.delay_variation);
        (*p_cb)(&qossu);
    }
}