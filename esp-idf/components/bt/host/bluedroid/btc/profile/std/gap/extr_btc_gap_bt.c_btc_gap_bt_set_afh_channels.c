#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  channels; } ;
struct TYPE_5__ {TYPE_1__ set_afh_channels; } ;
typedef  TYPE_2__ btc_gap_bt_args_t ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_DmSetAfhChannels (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btc_gap_bt_set_afh_channels_cmpl_callback ; 

__attribute__((used)) static void btc_gap_bt_set_afh_channels(btc_gap_bt_args_t *arg)
{
    BTA_DmSetAfhChannels(arg->set_afh_channels.channels, btc_gap_bt_set_afh_channels_cmpl_callback);
}