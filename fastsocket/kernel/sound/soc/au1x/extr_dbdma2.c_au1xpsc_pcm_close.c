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
struct snd_pcm_substream {int dummy; } ;

/* Variables and functions */
 size_t SUBSTREAM_TYPE (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  au1x_pcm_dbdma_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * au1xpsc_audio_pcmdma ; 

__attribute__((used)) static int au1xpsc_pcm_close(struct snd_pcm_substream *substream)
{
	au1x_pcm_dbdma_free(au1xpsc_audio_pcmdma[SUBSTREAM_TYPE(substream)]);
	return 0;
}