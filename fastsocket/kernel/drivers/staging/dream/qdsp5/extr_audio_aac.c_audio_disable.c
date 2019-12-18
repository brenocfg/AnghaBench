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
struct audio {scalar_t__ out_needed; int /*<<< orphan*/  audmgr; int /*<<< orphan*/  dec_id; int /*<<< orphan*/  audplay; int /*<<< orphan*/  read_wait; int /*<<< orphan*/  write_wait; scalar_t__ enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  auddec_dsp_config (struct audio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  audmgr_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  audpp_disable (int /*<<< orphan*/ ,struct audio*) ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 int /*<<< orphan*/  msm_adsp_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int audio_disable(struct audio *audio)
{
	dprintk("audio_disable()\n");
	if (audio->enabled) {
		audio->enabled = 0;
		auddec_dsp_config(audio, 0);
		wake_up(&audio->write_wait);
		wake_up(&audio->read_wait);
		msm_adsp_disable(audio->audplay);
		audpp_disable(audio->dec_id, audio);
		audmgr_disable(&audio->audmgr);
		audio->out_needed = 0;
	}
	return 0;
}