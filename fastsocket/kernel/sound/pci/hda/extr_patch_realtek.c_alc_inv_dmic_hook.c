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
struct snd_ctl_elem_value {int dummy; } ;
struct hda_codec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  alc_inv_dmic_sync (struct hda_codec*,int) ; 

__attribute__((used)) static void alc_inv_dmic_hook(struct hda_codec *codec,
			     struct snd_ctl_elem_value *ucontrol)
{
	alc_inv_dmic_sync(codec, false);
}