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
struct audio_in {int /*<<< orphan*/  audmgr; int /*<<< orphan*/  audpre; int /*<<< orphan*/  audrec; int /*<<< orphan*/  wait; scalar_t__ enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  audio_in_dsp_enable (struct audio_in*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  audmgr_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msm_adsp_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int audio_in_disable(struct audio_in *audio)
{
	if (audio->enabled) {
		audio->enabled = 0;

		audio_in_dsp_enable(audio, 0);

		wake_up(&audio->wait);

		msm_adsp_disable(audio->audrec);
		msm_adsp_disable(audio->audpre);
		audmgr_disable(&audio->audmgr);
	}
	return 0;
}