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
struct hda_codec {struct cmi_spec* spec; } ;
struct cmi_spec {scalar_t__ board_config; int /*<<< orphan*/  multi_init; } ;

/* Variables and functions */
 scalar_t__ CMI_ALLOUT ; 
 scalar_t__ CMI_AUTO ; 
 int /*<<< orphan*/  cmi9880_allout_init ; 
 int /*<<< orphan*/  cmi9880_basic_init ; 
 int /*<<< orphan*/  snd_hda_sequence_write (struct hda_codec*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cmi9880_init(struct hda_codec *codec)
{
	struct cmi_spec *spec = codec->spec;
	if (spec->board_config == CMI_ALLOUT)
		snd_hda_sequence_write(codec, cmi9880_allout_init);
	else
		snd_hda_sequence_write(codec, cmi9880_basic_init);
	if (spec->board_config == CMI_AUTO)
		snd_hda_sequence_write(codec, spec->multi_init);
	return 0;
}