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
struct audio {scalar_t__ out_needed; int /*<<< orphan*/  audmgr; int /*<<< orphan*/  wait; scalar_t__ enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  audio_allow_sleep (struct audio*) ; 
 int /*<<< orphan*/  audio_dsp_out_enable (struct audio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  audmgr_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  audpp_disable (int,struct audio*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int audio_disable(struct audio *audio)
{
	pr_info("audio_disable()\n");
	if (audio->enabled) {
		audio->enabled = 0;
		audio_dsp_out_enable(audio, 0);

		audpp_disable(-1, audio);

		wake_up(&audio->wait);
		audmgr_disable(&audio->audmgr);
		audio->out_needed = 0;
		audio_allow_sleep(audio);
	}
	return 0;
}