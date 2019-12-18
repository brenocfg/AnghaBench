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
struct xonar_wm87x6 {int* wm8766_regs; } ;
struct oxygen {struct xonar_wm87x6* model_data; } ;

/* Variables and functions */
 size_t WM8766_DAC_CTRL ; 
 int WM8766_PL_LEFT_LEFT ; 
 int WM8766_PL_RIGHT_RIGHT ; 
 int /*<<< orphan*/  wm8766_registers_init (struct oxygen*) ; 

__attribute__((used)) static void wm8766_init(struct oxygen *chip)
{
	struct xonar_wm87x6 *data = chip->model_data;

	data->wm8766_regs[WM8766_DAC_CTRL] =
		WM8766_PL_LEFT_LEFT | WM8766_PL_RIGHT_RIGHT;
	wm8766_registers_init(chip);
}