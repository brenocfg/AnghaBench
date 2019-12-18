#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  pwm_freq_div; int /*<<< orphan*/  gpio_pwm_pos; } ;
struct dib7000p_state {TYPE_1__ cfg; int /*<<< orphan*/  gpio_val; int /*<<< orphan*/  gpio_dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  dib7000p_write_word (struct dib7000p_state*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dib7000p_reset_gpio(struct dib7000p_state *st)
{
	/* reset the GPIOs */
	dprintk( "gpio dir: %x: val: %x, pwm_pos: %x",st->gpio_dir, st->gpio_val,st->cfg.gpio_pwm_pos);

	dib7000p_write_word(st, 1029, st->gpio_dir);
	dib7000p_write_word(st, 1030, st->gpio_val);

	/* TODO 1031 is P_gpio_od */

	dib7000p_write_word(st, 1032, st->cfg.gpio_pwm_pos);

	dib7000p_write_word(st, 1037, st->cfg.pwm_freq_div);
	return 0;
}