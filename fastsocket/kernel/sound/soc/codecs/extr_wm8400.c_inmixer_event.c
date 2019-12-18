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
typedef  int u16 ;
struct snd_soc_dapm_widget {int /*<<< orphan*/  codec; } ;
struct snd_kcontrol {int dummy; } ;

/* Variables and functions */
 int WM8400_AINLMUX_PWR ; 
 int WM8400_AINL_ENA ; 
 int WM8400_AINRMUX_PWR ; 
 int WM8400_AINR_ENA ; 
 int WM8400_INMIXL_PWR ; 
 int WM8400_INMIXR_PWR ; 
 int /*<<< orphan*/  WM8400_INTDRIVBITS ; 
 int /*<<< orphan*/  WM8400_POWER_MANAGEMENT_2 ; 
 int wm8400_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm8400_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int inmixer_event (struct snd_soc_dapm_widget *w,
	struct snd_kcontrol *kcontrol, int event)
{
	u16 reg, fakepower;

	reg = wm8400_read(w->codec, WM8400_POWER_MANAGEMENT_2);
	fakepower = wm8400_read(w->codec, WM8400_INTDRIVBITS);

	if (fakepower & ((1 << WM8400_INMIXL_PWR) |
		(1 << WM8400_AINLMUX_PWR))) {
		reg |= WM8400_AINL_ENA;
	} else {
		reg &= ~WM8400_AINL_ENA;
	}

	if (fakepower & ((1 << WM8400_INMIXR_PWR) |
		(1 << WM8400_AINRMUX_PWR))) {
		reg |= WM8400_AINR_ENA;
	} else {
		reg &= ~WM8400_AINL_ENA;
	}
	wm8400_write(w->codec, WM8400_POWER_MANAGEMENT_2, reg);

	return 0;
}