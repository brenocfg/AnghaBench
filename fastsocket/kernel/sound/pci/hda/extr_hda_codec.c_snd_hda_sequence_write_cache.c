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
struct hda_verb {int /*<<< orphan*/  param; int /*<<< orphan*/  verb; scalar_t__ nid; } ;
struct hda_codec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_hda_codec_write_cache (struct hda_codec*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void snd_hda_sequence_write_cache(struct hda_codec *codec,
				  const struct hda_verb *seq)
{
	for (; seq->nid; seq++)
		snd_hda_codec_write_cache(codec, seq->nid, 0, seq->verb,
					  seq->param);
}