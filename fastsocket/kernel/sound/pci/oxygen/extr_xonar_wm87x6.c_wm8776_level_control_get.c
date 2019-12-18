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
struct xonar_wm87x6 {int* wm8776_regs; } ;
struct snd_kcontrol {struct oxygen* private_data; } ;
struct TYPE_3__ {int* item; } ;
struct TYPE_4__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct oxygen {struct xonar_wm87x6* model_data; } ;

/* Variables and functions */
 size_t WM8776_ALCCTRL1 ; 
 size_t WM8776_ALCCTRL2 ; 
 int WM8776_LCEN ; 
 int WM8776_LCSEL_LIMITER ; 
 int WM8776_LCSEL_MASK ; 

__attribute__((used)) static int wm8776_level_control_get(struct snd_kcontrol *ctl,
				    struct snd_ctl_elem_value *value)
{
	struct oxygen *chip = ctl->private_data;
	struct xonar_wm87x6 *data = chip->model_data;

	if (!(data->wm8776_regs[WM8776_ALCCTRL2] & WM8776_LCEN))
		value->value.enumerated.item[0] = 0;
	else if ((data->wm8776_regs[WM8776_ALCCTRL1] & WM8776_LCSEL_MASK) ==
		 WM8776_LCSEL_LIMITER)
		value->value.enumerated.item[0] = 1;
	else
		value->value.enumerated.item[0] = 2;
	return 0;
}