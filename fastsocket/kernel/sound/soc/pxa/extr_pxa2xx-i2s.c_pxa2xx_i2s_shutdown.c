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
struct snd_soc_dai {int /*<<< orphan*/ * private_data; } ;
struct snd_pcm_substream {scalar_t__ stream; } ;

/* Variables and functions */
 int /*<<< orphan*/  SACR0 ; 
 int /*<<< orphan*/  SACR0_ENB ; 
 int SACR1 ; 
 int SACR1_DREC ; 
 int SACR1_DRPL ; 
 int /*<<< orphan*/  SAIMR ; 
 int /*<<< orphan*/  SAIMR_RFS ; 
 int /*<<< orphan*/  SAIMR_TFS ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_i2s ; 
 int /*<<< orphan*/  pxa_i2s_wait () ; 

__attribute__((used)) static void pxa2xx_i2s_shutdown(struct snd_pcm_substream *substream,
				struct snd_soc_dai *dai)
{
	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
		SACR1 |= SACR1_DRPL;
		SAIMR &= ~SAIMR_TFS;
	} else {
		SACR1 |= SACR1_DREC;
		SAIMR &= ~SAIMR_RFS;
	}

	if ((SACR1 & (SACR1_DREC | SACR1_DRPL)) == (SACR1_DREC | SACR1_DRPL)) {
		SACR0 &= ~SACR0_ENB;
		pxa_i2s_wait();
		if (dai->private_data != NULL) {
			clk_disable(clk_i2s);
			dai->private_data = NULL;
		}
	}
}