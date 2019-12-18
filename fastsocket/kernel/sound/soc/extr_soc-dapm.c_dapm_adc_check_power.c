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
struct snd_soc_dapm_widget {int /*<<< orphan*/  codec; scalar_t__ active; } ;

/* Variables and functions */
 int /*<<< orphan*/  dapm_clear_walk (int /*<<< orphan*/ ) ; 
 int dapm_generic_check_power (struct snd_soc_dapm_widget*) ; 
 int is_connected_input_ep (struct snd_soc_dapm_widget*) ; 

__attribute__((used)) static int dapm_adc_check_power(struct snd_soc_dapm_widget *w)
{
	int in;

	if (w->active) {
		in = is_connected_input_ep(w);
		dapm_clear_walk(w->codec);
		return in != 0;
	} else {
		return dapm_generic_check_power(w);
	}
}