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
struct snd_maya44 {int /*<<< orphan*/ * wm; int /*<<< orphan*/  ice; } ;

/* Variables and functions */
 int /*<<< orphan*/  WM8776_REG_ADC_MUX ; 
 int /*<<< orphan*/  wm8776_write_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void wm8776_select_input(struct snd_maya44 *chip, int idx, int line)
{
	wm8776_write_bits(chip->ice, &chip->wm[idx], WM8776_REG_ADC_MUX,
			  0x1f, 1 << line);
}