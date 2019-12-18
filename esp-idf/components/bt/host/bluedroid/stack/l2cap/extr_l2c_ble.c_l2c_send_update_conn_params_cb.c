#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int updating_param_flag; int /*<<< orphan*/  remote_bd_addr; int /*<<< orphan*/  current_used_conn_timeout; int /*<<< orphan*/  current_used_conn_latency; int /*<<< orphan*/  current_used_conn_interval; scalar_t__ updating_conn_min_interval; scalar_t__ updating_conn_max_interval; } ;
typedef  TYPE_1__ tL2C_LCB ;
struct TYPE_7__ {int /*<<< orphan*/  supervision_tout; int /*<<< orphan*/  slave_latency; int /*<<< orphan*/  conn_int; scalar_t__ min_conn_int; scalar_t__ max_conn_int; } ;
typedef  TYPE_2__ tBTM_LE_UPDATE_CONN_PRAMS ;
typedef  int /*<<< orphan*/  UINT8 ;
struct TYPE_8__ {int /*<<< orphan*/  (* update_conn_param_cb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ;} ;

/* Variables and functions */
 TYPE_5__ conn_param_update_cb ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 

void l2c_send_update_conn_params_cb(tL2C_LCB *p_lcb, UINT8 status)
{
    if(conn_param_update_cb.update_conn_param_cb != NULL){
        tBTM_LE_UPDATE_CONN_PRAMS update_param;
        //if myself update the connection parameters
        if (p_lcb->updating_param_flag){
            update_param.max_conn_int = p_lcb->updating_conn_max_interval;
            update_param.min_conn_int = p_lcb->updating_conn_min_interval;
            p_lcb->updating_param_flag = false;
        }else{
            // remote device update the connection parameters
            update_param.max_conn_int = update_param.min_conn_int = 0;
        }
        // current connection parameters
        update_param.conn_int = p_lcb->current_used_conn_interval;
        update_param.slave_latency = p_lcb->current_used_conn_latency;
        update_param.supervision_tout = p_lcb->current_used_conn_timeout;

        (conn_param_update_cb.update_conn_param_cb)(status, p_lcb->remote_bd_addr, &update_param);
    }
}