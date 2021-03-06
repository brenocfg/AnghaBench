#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  address; } ;
struct TYPE_6__ {TYPE_1__ bda; } ;
struct TYPE_7__ {TYPE_2__ read_rssi_delta; } ;
typedef  TYPE_3__ btc_gap_bt_args_t ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_DmBleReadRSSI (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTA_TRANSPORT_BR_EDR ; 
 int /*<<< orphan*/  btc_gap_bt_read_rssi_delta_cmpl_callback ; 

__attribute__((used)) static void btc_gap_bt_read_rssi_delta(btc_gap_bt_args_t *arg)
{
    BTA_DmBleReadRSSI(arg->read_rssi_delta.bda.address, BTA_TRANSPORT_BR_EDR, btc_gap_bt_read_rssi_delta_cmpl_callback);
}