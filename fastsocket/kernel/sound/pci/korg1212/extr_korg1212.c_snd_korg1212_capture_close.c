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
struct snd_korg1212 {size_t cardState; int capture_pid; int /*<<< orphan*/  lock; scalar_t__ periodsize; int /*<<< orphan*/ * capture_substream; } ;

/* Variables and functions */
 int /*<<< orphan*/  K1212_DEBUG_PRINTK (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_korg1212_CloseCard (struct snd_korg1212*) ; 
 struct snd_korg1212* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/ * stateName ; 

__attribute__((used)) static int snd_korg1212_capture_close(struct snd_pcm_substream *substream)
{
        unsigned long flags;
        struct snd_korg1212 *korg1212 = snd_pcm_substream_chip(substream);

	K1212_DEBUG_PRINTK("K1212_DEBUG: snd_korg1212_capture_close [%s]\n",
			   stateName[korg1212->cardState]);

        spin_lock_irqsave(&korg1212->lock, flags);

	korg1212->capture_pid = -1;
        korg1212->capture_substream = NULL;
        korg1212->periodsize = 0;

        spin_unlock_irqrestore(&korg1212->lock, flags);

	snd_korg1212_CloseCard(korg1212);
        return 0;
}