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
typedef  int uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_EARLY_LOGD (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  JOB_IDLE ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  s_job ; 
 int /*<<< orphan*/  sdio_slave_read_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_slave_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void event_cb(uint8_t pos)
{
    ESP_EARLY_LOGD(TAG, "event: %d", pos);
    switch(pos) {
        case 0:
            s_job = sdio_slave_read_reg(0);
            sdio_slave_write_reg(0, JOB_IDLE);
            break;
    }
}