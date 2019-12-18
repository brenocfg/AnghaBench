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
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  recv_flush_data () ; 
 int /*<<< orphan*/  recv_reset_counter () ; 
 int /*<<< orphan*/  send_flush_data () ; 
 int /*<<< orphan*/  send_reset_counter () ; 

esp_err_t sdio_slave_reset(void)
{
    send_flush_data();
    send_reset_counter();
    recv_flush_data();
    recv_reset_counter();
    return ESP_OK;
}