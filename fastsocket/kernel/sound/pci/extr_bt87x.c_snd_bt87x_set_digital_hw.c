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
struct TYPE_4__ {int /*<<< orphan*/  rate_max; int /*<<< orphan*/  rate_min; int /*<<< orphan*/  rates; } ;
struct snd_pcm_runtime {TYPE_2__ hw; } ;
struct TYPE_3__ {int /*<<< orphan*/  dig_rate; } ;
struct snd_bt87x {int reg_control; TYPE_1__ board; } ;

/* Variables and functions */
 int CTL_A_PWRDN ; 
 int CTL_DA_IOM_DA ; 
 TYPE_2__ snd_bt87x_digital_hw ; 
 int /*<<< orphan*/  snd_pcm_rate_to_rate_bit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_bt87x_set_digital_hw(struct snd_bt87x *chip, struct snd_pcm_runtime *runtime)
{
	chip->reg_control |= CTL_DA_IOM_DA | CTL_A_PWRDN;
	runtime->hw = snd_bt87x_digital_hw;
	runtime->hw.rates = snd_pcm_rate_to_rate_bit(chip->board.dig_rate);
	runtime->hw.rate_min = chip->board.dig_rate;
	runtime->hw.rate_max = chip->board.dig_rate;
	return 0;
}