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
typedef  int snd_pcm_uframes_t ;
struct TYPE_2__ {unsigned char* dma_area; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (unsigned char*,char,int) ; 

__attribute__((used)) static int bf5xx_pcm_silence(struct snd_pcm_substream *substream,
	int channel, snd_pcm_uframes_t pos, snd_pcm_uframes_t count)
{
	unsigned char *buf = substream->runtime->dma_area;
	buf += pos * 8 * 4;
	memset(buf, '\0', count * 8 * 4);

	return 0;
}