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
struct audmgr_config {int /*<<< orphan*/  snd_method; int /*<<< orphan*/  codec; int /*<<< orphan*/  def_method; int /*<<< orphan*/  rx_rate; int /*<<< orphan*/  tx_rate; } ;
struct audio {int enabled; int /*<<< orphan*/  audmgr; int /*<<< orphan*/  audplay; int /*<<< orphan*/  dec_id; scalar_t__ out_needed; scalar_t__ out_tail; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  RPC_AUD_DEF_CODEC_AMR_NB ; 
 int /*<<< orphan*/  RPC_AUD_DEF_METHOD_PLAYBACK ; 
 int /*<<< orphan*/  RPC_AUD_DEF_SAMPLE_RATE_48000 ; 
 int /*<<< orphan*/  RPC_AUD_DEF_SAMPLE_RATE_NONE ; 
 int /*<<< orphan*/  RPC_SND_METHOD_MIDI ; 
 int /*<<< orphan*/  audamrnb_dsp_event ; 
 int /*<<< orphan*/  audmgr_disable (int /*<<< orphan*/ *) ; 
 int audmgr_enable (int /*<<< orphan*/ *,struct audmgr_config*) ; 
 scalar_t__ audpp_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct audio*) ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 int /*<<< orphan*/  msm_adsp_disable (int /*<<< orphan*/ ) ; 
 scalar_t__ msm_adsp_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int audamrnb_enable(struct audio *audio)
{
	struct audmgr_config cfg;
	int rc;

	dprintk("audamrnb_enable()\n");

	if (audio->enabled)
		return 0;

	audio->out_tail = 0;
	audio->out_needed = 0;

	cfg.tx_rate = RPC_AUD_DEF_SAMPLE_RATE_NONE;
	cfg.rx_rate = RPC_AUD_DEF_SAMPLE_RATE_48000;
	cfg.def_method = RPC_AUD_DEF_METHOD_PLAYBACK;
	cfg.codec = RPC_AUD_DEF_CODEC_AMR_NB;
	cfg.snd_method = RPC_SND_METHOD_MIDI;

	rc = audmgr_enable(&audio->audmgr, &cfg);
	if (rc < 0)
		return rc;

	if (msm_adsp_enable(audio->audplay)) {
		pr_err("audio: msm_adsp_enable(audplay) failed\n");
		audmgr_disable(&audio->audmgr);
		return -ENODEV;
	}

	if (audpp_enable(audio->dec_id, audamrnb_dsp_event, audio)) {
		pr_err("audio: audpp_enable() failed\n");
		msm_adsp_disable(audio->audplay);
		audmgr_disable(&audio->audmgr);
		return -ENODEV;
	}
	audio->enabled = 1;
	return 0;
}