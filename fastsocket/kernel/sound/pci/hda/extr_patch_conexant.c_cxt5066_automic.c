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
struct hda_codec {struct conexant_spec* spec; } ;
struct conexant_spec {scalar_t__ asus; scalar_t__ hp_laptop; scalar_t__ thinkpad; scalar_t__ ideapad; scalar_t__ dell_vostro; } ;

/* Variables and functions */
 int /*<<< orphan*/  cxt5066_asus_automic (struct hda_codec*) ; 
 int /*<<< orphan*/  cxt5066_hp_laptop_automic (struct hda_codec*) ; 
 int /*<<< orphan*/  cxt5066_ideapad_automic (struct hda_codec*) ; 
 int /*<<< orphan*/  cxt5066_thinkpad_automic (struct hda_codec*) ; 
 int /*<<< orphan*/  cxt5066_vostro_automic (struct hda_codec*) ; 

__attribute__((used)) static void cxt5066_automic(struct hda_codec *codec)
{
	struct conexant_spec *spec = codec->spec;

	if (spec->dell_vostro)
		cxt5066_vostro_automic(codec);
	else if (spec->ideapad)
		cxt5066_ideapad_automic(codec);
	else if (spec->thinkpad)
		cxt5066_thinkpad_automic(codec);
	else if (spec->hp_laptop)
		cxt5066_hp_laptop_automic(codec);
	else if (spec->asus)
		cxt5066_asus_automic(codec);
}