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
struct hda_fixup {int dummy; } ;
struct hda_codec {struct alc_spec* spec; } ;
struct TYPE_2__ {int /*<<< orphan*/ * stream_analog_capture; int /*<<< orphan*/ * stream_analog_playback; } ;
struct alc_spec {TYPE_1__ gen; } ;

/* Variables and functions */
 int HDA_FIXUP_ACT_PROBE ; 
 int /*<<< orphan*/  alc269_44k_pcm_analog_capture ; 
 int /*<<< orphan*/  alc269_44k_pcm_analog_playback ; 

__attribute__((used)) static void alc269_fixup_pcm_44k(struct hda_codec *codec,
				 const struct hda_fixup *fix, int action)
{
	struct alc_spec *spec = codec->spec;

	if (action != HDA_FIXUP_ACT_PROBE)
		return;

	/* Due to a hardware problem on Lenovo Ideadpad, we need to
	 * fix the sample rate of analog I/O to 44.1kHz
	 */
	spec->gen.stream_analog_playback = &alc269_44k_pcm_analog_playback;
	spec->gen.stream_analog_capture = &alc269_44k_pcm_analog_capture;
}