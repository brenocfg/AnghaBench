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
struct hda_codec {int dummy; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 unsigned int AC_PWRST_D0 ; 
 unsigned int AC_PWRST_D3 ; 
 int /*<<< orphan*/  AC_VERB_SET_POWER_STATE ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  snd_hda_codec_read (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  snd_hda_codec_set_power_to_all (struct hda_codec*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void conexant_set_power(struct hda_codec *codec, hda_nid_t fg,
			       unsigned int power_state)
{
	if (power_state == AC_PWRST_D3)
		msleep(100);
	snd_hda_codec_read(codec, fg, 0, AC_VERB_SET_POWER_STATE,
			    power_state);
	/* partial workaround for "azx_get_response timeout" */
	if (power_state == AC_PWRST_D0)
		msleep(10);
	snd_hda_codec_set_power_to_all(codec, fg, power_state);
}