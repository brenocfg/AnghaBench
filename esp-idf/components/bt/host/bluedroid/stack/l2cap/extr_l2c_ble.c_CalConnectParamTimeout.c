#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int current_used_conn_latency; int current_used_conn_interval; } ;
typedef  TYPE_1__ tL2C_LCB ;
typedef  int UINT32 ;

/* Variables and functions */

UINT32 CalConnectParamTimeout(tL2C_LCB *p_lcb)
{
    UINT32 timeout = 6;
    if (p_lcb != NULL){
        //1.25 * conn_int *(1+ latency) *32
        timeout = (40 * ( 1 + p_lcb->current_used_conn_latency) * p_lcb->current_used_conn_interval + 500) / 1000;
        if (timeout < 1){
            timeout = 1;
        }else if (timeout > 120){
            timeout = 120;
        }
    }
    return timeout;
}