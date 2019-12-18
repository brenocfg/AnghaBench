#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct hda_hint {int /*<<< orphan*/  key; } ;
struct TYPE_3__ {int used; } ;
struct hda_codec {TYPE_1__ user_pins; TYPE_1__ hints; TYPE_1__ init_verbs; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 struct hda_hint* snd_array_elem (TYPE_1__*,int) ; 
 int /*<<< orphan*/  snd_array_free (TYPE_1__*) ; 

__attribute__((used)) static void clear_hwdep_elements(struct hda_codec *codec)
{
	int i;

	/* clear init verbs */
	snd_array_free(&codec->init_verbs);
	/* clear hints */
	for (i = 0; i < codec->hints.used; i++) {
		struct hda_hint *hint = snd_array_elem(&codec->hints, i);
		kfree(hint->key); /* we don't need to free hint->val */
	}
	snd_array_free(&codec->hints);
	snd_array_free(&codec->user_pins);
}