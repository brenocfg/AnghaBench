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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  BT_AV_TAG ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,int) ; 
 int s_pkt_cnt ; 
 int /*<<< orphan*/  write_ringbuf (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

void bt_app_a2d_data_cb(const uint8_t *data, uint32_t len)
{
    write_ringbuf(data, len);
    if (++s_pkt_cnt % 100 == 0) {
        ESP_LOGI(BT_AV_TAG, "Audio packet count %u", s_pkt_cnt);
    }
}