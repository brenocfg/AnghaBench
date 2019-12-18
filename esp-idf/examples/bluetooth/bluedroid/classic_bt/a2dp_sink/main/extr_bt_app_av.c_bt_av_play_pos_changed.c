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

/* Variables and functions */
 int /*<<< orphan*/  APP_RC_CT_TL_RN_PLAY_POS_CHANGE ; 
 int /*<<< orphan*/  ESP_AVRC_BIT_MASK_OP_TEST ; 
 int /*<<< orphan*/  ESP_AVRC_RN_PLAY_POS_CHANGED ; 
 int /*<<< orphan*/  esp_avrc_ct_send_register_notification_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ esp_avrc_rn_evt_bit_mask_operation (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_avrc_peer_rn_cap ; 

__attribute__((used)) static void bt_av_play_pos_changed(void)
{
    if (esp_avrc_rn_evt_bit_mask_operation(ESP_AVRC_BIT_MASK_OP_TEST, &s_avrc_peer_rn_cap,
                                           ESP_AVRC_RN_PLAY_POS_CHANGED)) {
        esp_avrc_ct_send_register_notification_cmd(APP_RC_CT_TL_RN_PLAY_POS_CHANGE, ESP_AVRC_RN_PLAY_POS_CHANGED, 10);
    }
}