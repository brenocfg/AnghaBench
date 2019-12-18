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

/* Variables and functions */
 int /*<<< orphan*/  snd_hda_jack_report_sync (struct hda_codec*) ; 
 int /*<<< orphan*/  snd_hda_jack_set_dirty_all (struct hda_codec*) ; 

__attribute__((used)) static void simple_hdmi_unsol_event(struct hda_codec *codec,
				    unsigned int res)
{
	snd_hda_jack_set_dirty_all(codec);
	snd_hda_jack_report_sync(codec);
}