#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct hda_codec {struct alc_spec* spec; } ;
struct TYPE_2__ {int /*<<< orphan*/  cap_sync_hook; } ;
struct alc_spec {int inv_dmic_fixup; TYPE_1__ gen; int /*<<< orphan*/  inv_dmic_pin; scalar_t__ inv_dmic_muted; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  alc_inv_dmic_hook ; 
 int /*<<< orphan*/  alc_inv_dmic_sw ; 
 int /*<<< orphan*/  snd_hda_gen_add_kctl (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int alc_add_inv_dmic_mixer(struct hda_codec *codec, hda_nid_t nid)
{
	struct alc_spec *spec = codec->spec;

	if (!snd_hda_gen_add_kctl(&spec->gen, NULL, &alc_inv_dmic_sw))
		return -ENOMEM;
	spec->inv_dmic_fixup = 1;
	spec->inv_dmic_muted = 0;
	spec->inv_dmic_pin = nid;
	spec->gen.cap_sync_hook = alc_inv_dmic_hook;
	return 0;
}