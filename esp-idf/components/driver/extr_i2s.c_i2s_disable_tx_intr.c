#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t i2s_port_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_3__ {scalar_t__ out_dscr_err; scalar_t__ out_eof; } ;
struct TYPE_4__ {TYPE_1__ int_ena; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_OK ; 
 TYPE_2__** I2S ; 
 int /*<<< orphan*/  I2S_ENTER_CRITICAL () ; 
 int /*<<< orphan*/  I2S_EXIT_CRITICAL () ; 

esp_err_t i2s_disable_tx_intr(i2s_port_t i2s_num)
{
    I2S_ENTER_CRITICAL();
    I2S[i2s_num]->int_ena.out_eof = 0;
    I2S[i2s_num]->int_ena.out_dscr_err = 0;
    I2S_EXIT_CRITICAL();
    return ESP_OK;
}