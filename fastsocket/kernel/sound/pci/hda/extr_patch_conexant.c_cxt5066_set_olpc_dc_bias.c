#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct hda_codec {struct conexant_spec* spec; } ;
struct conexant_spec {size_t dc_input_bias; } ;
struct TYPE_4__ {TYPE_1__* items; } ;
struct TYPE_3__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 TYPE_2__ cxt5066_olpc_dc_bias ; 
 int snd_hda_set_pin_ctl_cache (struct hda_codec*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cxt5066_set_olpc_dc_bias(struct hda_codec *codec)
{
	struct conexant_spec *spec = codec->spec;
	/* Even though port F is the DC input, the bias is controlled on port B.
	 * we also leave that port as an active input (but unselected) in DC mode
	 * just in case that is necessary to make the bias setting take effect. */
	return snd_hda_set_pin_ctl_cache(codec, 0x1a,
		cxt5066_olpc_dc_bias.items[spec->dc_input_bias].index);
}