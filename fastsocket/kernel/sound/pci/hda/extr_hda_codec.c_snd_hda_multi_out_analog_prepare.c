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
struct hda_spdif_out {int status; } ;
struct hda_multi_out {scalar_t__* dac_nids; scalar_t__ dig_out_used; scalar_t__ const hp_nid; scalar_t__ const* hp_out_nid; scalar_t__ const* extra_out_nid; int num_dacs; int /*<<< orphan*/  no_share_stream; scalar_t__ dig_out_nid; scalar_t__ share_spdif; } ;
struct hda_codec {int /*<<< orphan*/  spdif_mutex; } ;
typedef  scalar_t__ hda_nid_t ;
struct TYPE_2__ {int channels; } ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__ const*) ; 
 scalar_t__ HDA_DIG_ANALOG_DUP ; 
 scalar_t__ HDA_DIG_EXCLUSIVE ; 
 size_t HDA_FRONT ; 
 int IEC958_AES0_NONAUDIO ; 
 int /*<<< orphan*/  cleanup_dig_out_stream (struct hda_codec*,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setup_dig_out_stream (struct hda_codec*,scalar_t__,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  snd_hda_codec_setup_stream (struct hda_codec*,scalar_t__ const,unsigned int,int,unsigned int) ; 
 scalar_t__ snd_hda_is_supported_format (struct hda_codec*,scalar_t__,unsigned int) ; 
 struct hda_spdif_out* snd_hda_spdif_out_of_nid (struct hda_codec*,scalar_t__) ; 

int snd_hda_multi_out_analog_prepare(struct hda_codec *codec,
				     struct hda_multi_out *mout,
				     unsigned int stream_tag,
				     unsigned int format,
				     struct snd_pcm_substream *substream)
{
	const hda_nid_t *nids = mout->dac_nids;
	int chs = substream->runtime->channels;
	struct hda_spdif_out *spdif;
	int i;

	mutex_lock(&codec->spdif_mutex);
	spdif = snd_hda_spdif_out_of_nid(codec, mout->dig_out_nid);
	if (mout->dig_out_nid && mout->share_spdif &&
	    mout->dig_out_used != HDA_DIG_EXCLUSIVE) {
		if (chs == 2 &&
		    snd_hda_is_supported_format(codec, mout->dig_out_nid,
						format) &&
		    !(spdif->status & IEC958_AES0_NONAUDIO)) {
			mout->dig_out_used = HDA_DIG_ANALOG_DUP;
			setup_dig_out_stream(codec, mout->dig_out_nid,
					     stream_tag, format);
		} else {
			mout->dig_out_used = 0;
			cleanup_dig_out_stream(codec, mout->dig_out_nid);
		}
	}
	mutex_unlock(&codec->spdif_mutex);

	/* front */
	snd_hda_codec_setup_stream(codec, nids[HDA_FRONT], stream_tag,
				   0, format);
	if (!mout->no_share_stream &&
	    mout->hp_nid && mout->hp_nid != nids[HDA_FRONT])
		/* headphone out will just decode front left/right (stereo) */
		snd_hda_codec_setup_stream(codec, mout->hp_nid, stream_tag,
					   0, format);
	/* extra outputs copied from front */
	for (i = 0; i < ARRAY_SIZE(mout->hp_out_nid); i++)
		if (!mout->no_share_stream && mout->hp_out_nid[i])
			snd_hda_codec_setup_stream(codec,
						   mout->hp_out_nid[i],
						   stream_tag, 0, format);
	for (i = 0; i < ARRAY_SIZE(mout->extra_out_nid); i++)
		if (!mout->no_share_stream && mout->extra_out_nid[i])
			snd_hda_codec_setup_stream(codec,
						   mout->extra_out_nid[i],
						   stream_tag, 0, format);

	/* surrounds */
	for (i = 1; i < mout->num_dacs; i++) {
		if (chs >= (i + 1) * 2) /* independent out */
			snd_hda_codec_setup_stream(codec, nids[i], stream_tag,
						   i * 2, format);
		else if (!mout->no_share_stream) /* copy front */
			snd_hda_codec_setup_stream(codec, nids[i], stream_tag,
						   0, format);
	}
	return 0;
}