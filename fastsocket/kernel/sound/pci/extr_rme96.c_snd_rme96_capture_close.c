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
struct rme96 {int /*<<< orphan*/  lock; scalar_t__ capture_periodsize; int /*<<< orphan*/ * capture_substream; } ;

/* Variables and functions */
 scalar_t__ RME96_ISRECORDING (struct rme96*) ; 
 struct rme96* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_rme96_capture_stop (struct rme96*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
snd_rme96_capture_close(struct snd_pcm_substream *substream)
{
	struct rme96 *rme96 = snd_pcm_substream_chip(substream);
	
	spin_lock_irq(&rme96->lock);	
	if (RME96_ISRECORDING(rme96)) {
		snd_rme96_capture_stop(rme96);
	}
	rme96->capture_substream = NULL;
	rme96->capture_periodsize = 0;
	spin_unlock_irq(&rme96->lock);
	return 0;
}