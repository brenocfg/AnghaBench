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
struct conexant_spec {int auto_mic; int cur_adc_idx; scalar_t__* adc_nids; scalar_t__ cur_adc; int /*<<< orphan*/  cur_adc_format; int /*<<< orphan*/  cur_adc_stream_tag; } ;
typedef  scalar_t__ hda_nid_t ;

/* Variables and functions */
 int AUTO_MIC_PORTC ; 
 int /*<<< orphan*/  __snd_hda_codec_cleanup_stream (struct hda_codec*,scalar_t__,int) ; 
 int /*<<< orphan*/  snd_hda_codec_setup_stream (struct hda_codec*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int snd_hda_jack_detect (struct hda_codec*,int) ; 

__attribute__((used)) static void cxt5051_portc_automic(struct hda_codec *codec)
{
	struct conexant_spec *spec = codec->spec;
	unsigned int present;
	hda_nid_t new_adc;

	if (!(spec->auto_mic & AUTO_MIC_PORTC))
		return;
	present = snd_hda_jack_detect(codec, 0x18);
	if (present)
		spec->cur_adc_idx = 1;
	else
		spec->cur_adc_idx = 0;
	new_adc = spec->adc_nids[spec->cur_adc_idx];
	if (spec->cur_adc && spec->cur_adc != new_adc) {
		/* stream is running, let's swap the current ADC */
		__snd_hda_codec_cleanup_stream(codec, spec->cur_adc, 1);
		spec->cur_adc = new_adc;
		snd_hda_codec_setup_stream(codec, new_adc,
					   spec->cur_adc_stream_tag, 0,
					   spec->cur_adc_format);
	}
}