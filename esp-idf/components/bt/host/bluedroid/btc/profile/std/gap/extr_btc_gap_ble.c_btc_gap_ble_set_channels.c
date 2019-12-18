#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  esp_gap_ble_channels ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_DmBleSetChannels (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btc_gap_ble_set_channels_cmpl_callback ; 

__attribute__((used)) static void btc_gap_ble_set_channels(esp_gap_ble_channels channels)
{
    BTA_DmBleSetChannels(channels, btc_gap_ble_set_channels_cmpl_callback);
}