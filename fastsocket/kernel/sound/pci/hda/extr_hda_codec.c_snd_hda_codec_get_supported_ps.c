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
 int /*<<< orphan*/  AC_PAR_POWER_STATE ; 
 int snd_hda_param_read (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool snd_hda_codec_get_supported_ps(struct hda_codec *codec, hda_nid_t fg,
				unsigned int power_state)
{
	int sup = snd_hda_param_read(codec, fg, AC_PAR_POWER_STATE);

	if (sup == -1)
		return false;
	if (sup & power_state)
		return true;
	else
		return false;
}