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
struct TYPE_2__ {scalar_t__ unsol_event; } ;
struct hda_codec {TYPE_1__ patch_ops; struct conexant_spec* spec; } ;
struct conexant_spec {int auto_mic; } ;

/* Variables and functions */
 int AUTO_MIC_PORTB ; 
 int AUTO_MIC_PORTC ; 
 int /*<<< orphan*/  CXT5051_PORTB_EVENT ; 
 int /*<<< orphan*/  CXT5051_PORTC_EVENT ; 
 int /*<<< orphan*/  conexant_init (struct hda_codec*) ; 
 int /*<<< orphan*/  cxt5051_hp_automute (struct hda_codec*) ; 
 int /*<<< orphan*/  cxt5051_init_mic_port (struct hda_codec*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxt5051_portb_automic (struct hda_codec*) ; 
 int /*<<< orphan*/  cxt5051_portc_automic (struct hda_codec*) ; 

__attribute__((used)) static int cxt5051_init(struct hda_codec *codec)
{
	struct conexant_spec *spec = codec->spec;

	conexant_init(codec);

	if (spec->auto_mic & AUTO_MIC_PORTB)
		cxt5051_init_mic_port(codec, 0x17, CXT5051_PORTB_EVENT);
	if (spec->auto_mic & AUTO_MIC_PORTC)
		cxt5051_init_mic_port(codec, 0x18, CXT5051_PORTC_EVENT);

	if (codec->patch_ops.unsol_event) {
		cxt5051_hp_automute(codec);
		cxt5051_portb_automic(codec);
		cxt5051_portc_automic(codec);
	}
	return 0;
}