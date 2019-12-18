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
struct hda_pintbl {int /*<<< orphan*/  val; scalar_t__ nid; } ;
struct hda_codec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_hda_codec_set_pincfg (struct hda_codec*,scalar_t__,int /*<<< orphan*/ ) ; 

void snd_hda_apply_pincfgs(struct hda_codec *codec,
			   const struct hda_pintbl *cfg)
{
	for (; cfg->nid; cfg++)
		snd_hda_codec_set_pincfg(codec, cfg->nid, cfg->val);
}