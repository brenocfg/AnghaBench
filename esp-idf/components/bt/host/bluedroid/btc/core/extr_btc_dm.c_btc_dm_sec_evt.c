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
typedef  int /*<<< orphan*/  tBTA_DM_SEC_EVT ;
typedef  int /*<<< orphan*/  tBTA_DM_SEC ;
struct TYPE_3__ {int /*<<< orphan*/  act; int /*<<< orphan*/  pid; int /*<<< orphan*/  sig; } ;
typedef  TYPE_1__ btc_msg_t ;
typedef  int /*<<< orphan*/  btc_dm_sec_args_t ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_PID_DM_SEC ; 
 int /*<<< orphan*/  BTC_SIG_API_CB ; 
 int /*<<< orphan*/  btc_dm_sec_arg_deep_copy ; 
 int /*<<< orphan*/  btc_transfer_context (TYPE_1__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

void btc_dm_sec_evt(tBTA_DM_SEC_EVT event, tBTA_DM_SEC *data)
{
    btc_msg_t msg;

    msg.sig = BTC_SIG_API_CB;
    msg.pid = BTC_PID_DM_SEC;
    msg.act = event;

    btc_transfer_context(&msg, (btc_dm_sec_args_t *)data, sizeof(btc_dm_sec_args_t), btc_dm_sec_arg_deep_copy);
}