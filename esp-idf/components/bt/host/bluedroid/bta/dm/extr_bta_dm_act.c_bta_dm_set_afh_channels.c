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
struct TYPE_4__ {int /*<<< orphan*/  set_afh_cb; int /*<<< orphan*/  channels; } ;
struct TYPE_5__ {TYPE_1__ set_afh_channels; } ;
typedef  TYPE_2__ tBTA_DM_MSG ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_SetAfhChannels (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void bta_dm_set_afh_channels (tBTA_DM_MSG *p_data)
{
#if CLASSIC_BT_INCLUDED
    BTM_SetAfhChannels (p_data->set_afh_channels.channels, p_data->set_afh_channels.set_afh_cb);
#endif /// CLASSIC_BT_INCLUDED
}