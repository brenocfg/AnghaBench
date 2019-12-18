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
struct dp_audio_infoframe {int type; int len; int ver; int CC02_CT47; int CA; } ;
struct hdmi_audio_infoframe {int type; int ver; int len; int CC02_CT47; int CA; } ;
union audio_infoframe {int /*<<< orphan*/  bytes; struct dp_audio_infoframe dp; struct hdmi_audio_infoframe hdmi; } ;
struct snd_pcm_substream {TYPE_1__* runtime; } ;
struct TYPE_4__ {int conn_type; } ;
struct hdmi_eld {TYPE_2__ info; int /*<<< orphan*/  monitor_present; } ;
struct hdmi_spec_per_pin {int non_pcm; struct hdmi_eld sink_eld; int /*<<< orphan*/  pin_nid; } ;
struct hdmi_spec {int dummy; } ;
struct hda_codec {struct hdmi_spec* spec; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;
typedef  int /*<<< orphan*/  ai ;
struct TYPE_3__ {int channels; } ;

/* Variables and functions */
 struct hdmi_spec_per_pin* get_pin (struct hdmi_spec*,int) ; 
 int hdmi_channel_allocation (struct hdmi_eld*,int) ; 
 int /*<<< orphan*/  hdmi_checksum_audio_infoframe (struct hdmi_audio_infoframe*) ; 
 int /*<<< orphan*/  hdmi_fill_audio_infoframe (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hdmi_infoframe_uptodate (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hdmi_setup_channel_mapping (struct hda_codec*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  hdmi_start_infoframe_trans (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdmi_stop_infoframe_trans (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (union audio_infoframe*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_printd (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_printdd (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hdmi_setup_audio_infoframe(struct hda_codec *codec, int pin_idx,
				       bool non_pcm,
				       struct snd_pcm_substream *substream)
{
	struct hdmi_spec *spec = codec->spec;
	struct hdmi_spec_per_pin *per_pin = get_pin(spec, pin_idx);
	hda_nid_t pin_nid = per_pin->pin_nid;
	int channels = substream->runtime->channels;
	struct hdmi_eld *eld;
	int ca;
	union audio_infoframe ai;

	eld = &per_pin->sink_eld;
	if (!eld->monitor_present)
		return;

	ca = hdmi_channel_allocation(eld, channels);

	memset(&ai, 0, sizeof(ai));
	if (eld->info.conn_type == 0) { /* HDMI */
		struct hdmi_audio_infoframe *hdmi_ai = &ai.hdmi;

		hdmi_ai->type		= 0x84;
		hdmi_ai->ver		= 0x01;
		hdmi_ai->len		= 0x0a;
		hdmi_ai->CC02_CT47	= channels - 1;
		hdmi_ai->CA		= ca;
		hdmi_checksum_audio_infoframe(hdmi_ai);
	} else if (eld->info.conn_type == 1) { /* DisplayPort */
		struct dp_audio_infoframe *dp_ai = &ai.dp;

		dp_ai->type		= 0x84;
		dp_ai->len		= 0x1b;
		dp_ai->ver		= 0x11 << 2;
		dp_ai->CC02_CT47	= channels - 1;
		dp_ai->CA		= ca;
	} else {
		snd_printd("HDMI: unknown connection type at pin %d\n",
			    pin_nid);
		return;
	}

	/*
	 * sizeof(ai) is used instead of sizeof(*hdmi_ai) or
	 * sizeof(*dp_ai) to avoid partial match/update problems when
	 * the user switches between HDMI/DP monitors.
	 */
	if (!hdmi_infoframe_uptodate(codec, pin_nid, ai.bytes,
					sizeof(ai))) {
		snd_printdd("hdmi_setup_audio_infoframe: "
			    "pin=%d channels=%d\n",
			    pin_nid,
			    channels);
		hdmi_setup_channel_mapping(codec, pin_nid, non_pcm, ca);
		hdmi_stop_infoframe_trans(codec, pin_nid);
		hdmi_fill_audio_infoframe(codec, pin_nid,
					    ai.bytes, sizeof(ai));
		hdmi_start_infoframe_trans(codec, pin_nid);
	} else {
		/* For non-pcm audio switch, setup new channel mapping
		 * accordingly */
		if (per_pin->non_pcm != non_pcm)
			hdmi_setup_channel_mapping(codec, pin_nid, non_pcm, ca);
	}

	per_pin->non_pcm = non_pcm;
}