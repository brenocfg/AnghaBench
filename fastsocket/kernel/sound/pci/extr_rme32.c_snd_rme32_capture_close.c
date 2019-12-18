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
struct rme32 {int /*<<< orphan*/  lock; scalar_t__ capture_periodsize; int /*<<< orphan*/ * capture_substream; } ;

/* Variables and functions */
 struct rme32* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_rme32_capture_close(struct snd_pcm_substream *substream)
{
	struct rme32 *rme32 = snd_pcm_substream_chip(substream);

	spin_lock_irq(&rme32->lock);
	rme32->capture_substream = NULL;
	rme32->capture_periodsize = 0;
	spin_unlock(&rme32->lock);
	return 0;
}