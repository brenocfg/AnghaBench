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
struct via_spec {int /*<<< orphan*/  gen; } ;
struct hda_codec {struct via_spec* spec; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct via_spec*) ; 
 int /*<<< orphan*/  snd_hda_gen_spec_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vt1708_stop_hp_work (struct hda_codec*) ; 

__attribute__((used)) static void via_free(struct hda_codec *codec)
{
	struct via_spec *spec = codec->spec;

	if (!spec)
		return;

	vt1708_stop_hp_work(codec);
	snd_hda_gen_spec_free(&spec->gen);
	kfree(spec);
}