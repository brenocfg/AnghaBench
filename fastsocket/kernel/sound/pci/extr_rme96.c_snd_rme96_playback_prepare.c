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
struct rme96 {int /*<<< orphan*/  lock; scalar_t__ iobase; } ;

/* Variables and functions */
 scalar_t__ RME96_IO_RESET_PLAY_POS ; 
 scalar_t__ RME96_ISPLAYING (struct rme96*) ; 
 struct rme96* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_rme96_playback_stop (struct rme96*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
snd_rme96_playback_prepare(struct snd_pcm_substream *substream)
{
	struct rme96 *rme96 = snd_pcm_substream_chip(substream);
	
	spin_lock_irq(&rme96->lock);	
	if (RME96_ISPLAYING(rme96)) {
		snd_rme96_playback_stop(rme96);
	}
	writel(0, rme96->iobase + RME96_IO_RESET_PLAY_POS);
	spin_unlock_irq(&rme96->lock);
	return 0;
}