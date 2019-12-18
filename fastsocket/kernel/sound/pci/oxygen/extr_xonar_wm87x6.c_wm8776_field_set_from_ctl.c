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
typedef  unsigned int u8 ;
typedef  unsigned int u16 ;
struct xonar_wm87x6 {int* wm8776_regs; } ;
struct snd_kcontrol {unsigned int private_value; struct oxygen* private_data; } ;
struct oxygen {struct xonar_wm87x6* model_data; } ;

/* Variables and functions */
 unsigned int LC_CONTROL_ALC ; 
 unsigned int LC_CONTROL_LIMITER ; 
 size_t WM8776_ALCCTRL1 ; 
 int WM8776_LCSEL_LIMITER ; 
 int WM8776_LCSEL_MASK ; 
 int /*<<< orphan*/  wm8776_write_cached (struct oxygen*,unsigned int,unsigned int) ; 

__attribute__((used)) static void wm8776_field_set_from_ctl(struct snd_kcontrol *ctl)
{
	struct oxygen *chip = ctl->private_data;
	struct xonar_wm87x6 *data = chip->model_data;
	unsigned int value, reg_index, mode;
	u8 min, max, shift;
	u16 mask, reg_value;
	bool invert;

	if ((data->wm8776_regs[WM8776_ALCCTRL1] & WM8776_LCSEL_MASK) ==
	    WM8776_LCSEL_LIMITER)
		mode = LC_CONTROL_LIMITER;
	else
		mode = LC_CONTROL_ALC;
	if (!(ctl->private_value & mode))
		return;

	value = ctl->private_value & 0xf;
	min = (ctl->private_value >> 8) & 0xf;
	max = (ctl->private_value >> 12) & 0xf;
	mask = (ctl->private_value >> 16) & 0xf;
	shift = (ctl->private_value >> 20) & 0xf;
	reg_index = (ctl->private_value >> 24) & 0x1f;
	invert = (ctl->private_value >> 29) & 0x1;

	if (invert)
		value = max - (value - min);
	reg_value = data->wm8776_regs[reg_index];
	reg_value &= ~(mask << shift);
	reg_value |= value << shift;
	wm8776_write_cached(chip, reg_index, reg_value);
}