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
struct hda_codec {struct alc_spec* spec; } ;
struct alc_spec {int /*<<< orphan*/  (* shutup ) (struct hda_codec*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  snd_hda_shutup_pins (struct hda_codec*) ; 
 int /*<<< orphan*/  stub1 (struct hda_codec*) ; 

__attribute__((used)) static inline void alc_shutup(struct hda_codec *codec)
{
	struct alc_spec *spec = codec->spec;

	if (spec && spec->shutup)
		spec->shutup(codec);
	snd_hda_shutup_pins(codec);
}