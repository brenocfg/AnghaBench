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
 int WM8990_AINLMUX_PWR_BIT ; 
 int WM8990_AINL_ENA ; 
 int WM8990_AINRMUX_PWR_BIT ; 
 int WM8990_AINR_ENA ; 
 int WM8990_INMIXL_PWR_BIT ; 
 int WM8990_INMIXR_PWR_BIT ; 
 int /*<<< orphan*/  WM8990_INTDRIVBITS ; 
 int /*<<< orphan*/  WM8990_POWER_MANAGEMENT_2 ; 
 int snd_soc_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int inmixer_event(struct snd_soc_dapm_widget *w,
	struct snd_kcontrol *kcontrol, int event)
{
	u16 reg, fakepower;

	reg = snd_soc_read(w->codec, WM8990_POWER_MANAGEMENT_2);
	fakepower = snd_soc_read(w->codec, WM8990_INTDRIVBITS);

	if (fakepower & ((1 << WM8990_INMIXL_PWR_BIT) |
		(1 << WM8990_AINLMUX_PWR_BIT))) {
		reg |= WM8990_AINL_ENA;
	} else {
		reg &= ~WM8990_AINL_ENA;
	}

	if (fakepower & ((1 << WM8990_INMIXR_PWR_BIT) |
		(1 << WM8990_AINRMUX_PWR_BIT))) {
		reg |= WM8990_AINR_ENA;
	} else {
		reg &= ~WM8990_AINL_ENA;
	}
	snd_soc_write(w->codec, WM8990_POWER_MANAGEMENT_2, reg);

	return 0;
}