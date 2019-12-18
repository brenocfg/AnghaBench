#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int freq_hz; int /*<<< orphan*/  clk_cfg; int /*<<< orphan*/  duty_resolution; int /*<<< orphan*/  timer_num; int /*<<< orphan*/  speed_mode; } ;
typedef  TYPE_1__ ledc_timer_config_t ;
struct TYPE_6__ {int duty; int /*<<< orphan*/  hpoint; int /*<<< orphan*/  gpio_num; int /*<<< orphan*/  intr_type; int /*<<< orphan*/  timer_sel; int /*<<< orphan*/  channel; int /*<<< orphan*/  speed_mode; } ;
typedef  TYPE_2__ ledc_channel_config_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERROR_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LEDC_AUTO_CLK ; 
 int /*<<< orphan*/  LEDC_CHANNEL_1 ; 
 int /*<<< orphan*/  LEDC_HIGH_SPEED_MODE ; 
 int /*<<< orphan*/  LEDC_INTR_DISABLE ; 
 int /*<<< orphan*/  LEDC_TIMER_1 ; 
 int /*<<< orphan*/  LEDC_TIMER_10_BIT ; 
 int /*<<< orphan*/  PULSE_IO ; 
 int /*<<< orphan*/  ledc_channel_config (TYPE_2__*) ; 
 int /*<<< orphan*/  ledc_timer_config (TYPE_1__*) ; 

__attribute__((used)) static void produce_pulse(void)
{
    ledc_timer_config_t ledc_timer = {
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .timer_num  = LEDC_TIMER_1,
        .duty_resolution = LEDC_TIMER_10_BIT,
        .freq_hz = 1,
        .clk_cfg = LEDC_AUTO_CLK,
    };
    ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

    ledc_channel_config_t ledc_channel = {
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .channel = LEDC_CHANNEL_1,
        .timer_sel = LEDC_TIMER_1,
        .intr_type = LEDC_INTR_DISABLE,
        .gpio_num = PULSE_IO,
        .duty = 100,
        .hpoint = 0,
    };
    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));
}