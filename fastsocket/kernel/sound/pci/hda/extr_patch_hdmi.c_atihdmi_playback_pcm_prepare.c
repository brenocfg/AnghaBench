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
struct snd_pcm_substream {TYPE_1__* runtime; } ;
struct hdmi_spec_per_cvt {int /*<<< orphan*/  cvt_nid; } ;
struct hdmi_spec {int dummy; } ;
struct hda_pcm_stream {int dummy; } ;
struct hda_codec {struct hdmi_spec* spec; } ;
struct TYPE_2__ {int channels; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_VERB_SET_CVT_CHAN_COUNT ; 
 int /*<<< orphan*/  AC_VERB_SET_HDMI_CHAN_SLOT ; 
 struct hdmi_spec_per_cvt* get_cvt (struct hdmi_spec*,int /*<<< orphan*/ ) ; 
 int simple_playback_pcm_prepare (struct hda_pcm_stream*,struct hda_codec*,unsigned int,unsigned int,struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_hda_codec_write (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int atihdmi_playback_pcm_prepare(struct hda_pcm_stream *hinfo,
					struct hda_codec *codec,
					unsigned int stream_tag,
					unsigned int format,
					struct snd_pcm_substream *substream)
{
	struct hdmi_spec *spec = codec->spec;
	struct hdmi_spec_per_cvt *per_cvt = get_cvt(spec, 0);
	int chans = substream->runtime->channels;
	int i, err;

	err = simple_playback_pcm_prepare(hinfo, codec, stream_tag, format,
					  substream);
	if (err < 0)
		return err;
	snd_hda_codec_write(codec, per_cvt->cvt_nid, 0,
			    AC_VERB_SET_CVT_CHAN_COUNT, chans - 1);
	/* FIXME: XXX */
	for (i = 0; i < chans; i++) {
		snd_hda_codec_write(codec, per_cvt->cvt_nid, 0,
				    AC_VERB_SET_HDMI_CHAN_SLOT,
				    (i << 4) | i);
	}
	return 0;
}