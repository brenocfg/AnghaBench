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
 int E740_AUDIO_IN ; 
 int E740_AUDIO_OUT ; 
 int /*<<< orphan*/  GPIO_E740_AMP_ON ; 
 int /*<<< orphan*/  GPIO_E740_MIC_ON ; 
 int /*<<< orphan*/  GPIO_E740_WM9705_nAVDD2 ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void e740_sync_audio_power(int status)
{
	gpio_set_value(GPIO_E740_WM9705_nAVDD2, !status);
	gpio_set_value(GPIO_E740_AMP_ON, (status & E740_AUDIO_OUT) ? 1 : 0);
	gpio_set_value(GPIO_E740_MIC_ON, (status & E740_AUDIO_IN) ? 1 : 0);
}