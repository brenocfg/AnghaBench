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
typedef  int /*<<< orphan*/  u32 ;
struct hda_codec {int dummy; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 int get_jack_plug_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_pin_sense (struct hda_codec*,int /*<<< orphan*/ ) ; 

int snd_hda_jack_detect(struct hda_codec *codec, hda_nid_t nid)
{
	u32 sense = snd_hda_pin_sense(codec, nid);
	return get_jack_plug_state(sense);
}