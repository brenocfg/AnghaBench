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
struct conexant_spec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct conexant_spec*) ; 
 int /*<<< orphan*/  snd_hda_detach_beep_device (struct hda_codec*) ; 

__attribute__((used)) static void conexant_free(struct hda_codec *codec)
{
	struct conexant_spec *spec = codec->spec;
	snd_hda_detach_beep_device(codec);
	kfree(spec);
}