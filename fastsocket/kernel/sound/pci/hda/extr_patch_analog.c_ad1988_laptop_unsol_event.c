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
 unsigned int AD1988_HP_EVENT ; 
 int /*<<< orphan*/  ad1988_laptop_hp_off ; 
 int /*<<< orphan*/  ad1988_laptop_hp_on ; 
 scalar_t__ snd_hda_jack_detect (struct hda_codec*,int) ; 
 int /*<<< orphan*/  snd_hda_sequence_write (struct hda_codec*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ad1988_laptop_unsol_event(struct hda_codec *codec, unsigned int res)
{
	if ((res >> 26) != AD1988_HP_EVENT)
		return;
	if (snd_hda_jack_detect(codec, 0x11))
		snd_hda_sequence_write(codec, ad1988_laptop_hp_on);
	else
		snd_hda_sequence_write(codec, ad1988_laptop_hp_off);
}