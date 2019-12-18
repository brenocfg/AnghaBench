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
struct audio_in {int enabled; scalar_t__ type; int /*<<< orphan*/  audrec; int /*<<< orphan*/  audpre; int /*<<< orphan*/  audmgr; int /*<<< orphan*/  samp_rate; } ;

/* Variables and functions */
 scalar_t__ AUDREC_CMD_TYPE_0_INDEX_WAV ; 
 int ENODEV ; 
 int /*<<< orphan*/  RPC_AUD_DEF_CODEC_AAC ; 
 int /*<<< orphan*/  RPC_AUD_DEF_CODEC_PCM ; 
 int /*<<< orphan*/  RPC_AUD_DEF_METHOD_RECORD ; 
 int /*<<< orphan*/  RPC_AUD_DEF_SAMPLE_RATE_NONE ; 
 int /*<<< orphan*/  RPC_SND_METHOD_MIDI ; 
 int /*<<< orphan*/  audio_in_dsp_enable (struct audio_in*,int) ; 
 int audmgr_enable (int /*<<< orphan*/ *,struct audmgr_config*) ; 
 scalar_t__ msm_adsp_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int audio_in_enable(struct audio_in *audio)
{
	struct audmgr_config cfg;
	int rc;

	if (audio->enabled)
		return 0;

	cfg.tx_rate = audio->samp_rate;
	cfg.rx_rate = RPC_AUD_DEF_SAMPLE_RATE_NONE;
	cfg.def_method = RPC_AUD_DEF_METHOD_RECORD;
	if (audio->type == AUDREC_CMD_TYPE_0_INDEX_WAV)
		cfg.codec = RPC_AUD_DEF_CODEC_PCM;
	else
		cfg.codec = RPC_AUD_DEF_CODEC_AAC;
	cfg.snd_method = RPC_SND_METHOD_MIDI;

	rc = audmgr_enable(&audio->audmgr, &cfg);
	if (rc < 0)
		return rc;

	if (msm_adsp_enable(audio->audpre)) {
		pr_err("audrec: msm_adsp_enable(audpre) failed\n");
		return -ENODEV;
	}
	if (msm_adsp_enable(audio->audrec)) {
		pr_err("audrec: msm_adsp_enable(audrec) failed\n");
		return -ENODEV;
	}

	audio->enabled = 1;
	audio_in_dsp_enable(audio, 1);

	return 0;
}