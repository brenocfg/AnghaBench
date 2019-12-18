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
struct nm256_stream {unsigned long dma_size; scalar_t__ buf; } ;
struct nm256 {int dummy; } ;
typedef  int /*<<< orphan*/  snd_pcm_uframes_t ;
struct TYPE_2__ {struct nm256_stream* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  NM_RBUFFER_CURRP ; 
 int /*<<< orphan*/  bytes_to_frames (TYPE_1__*,unsigned long) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 unsigned long snd_nm256_readl (struct nm256*,int /*<<< orphan*/ ) ; 
 struct nm256* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static snd_pcm_uframes_t
snd_nm256_capture_pointer(struct snd_pcm_substream *substream)
{
	struct nm256 *chip = snd_pcm_substream_chip(substream);
	struct nm256_stream *s = substream->runtime->private_data;
	unsigned long curp;

	if (snd_BUG_ON(!s))
		return 0;
	curp = snd_nm256_readl(chip, NM_RBUFFER_CURRP) - (unsigned long)s->buf;
	curp %= s->dma_size;	
	return bytes_to_frames(substream->runtime, curp);
}