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
struct snd_ice1712 {int /*<<< orphan*/  reg_lock; } ;
struct TYPE_2__ {int channels; int /*<<< orphan*/  dma_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BURST ; 
 scalar_t__ ICEMT1724 (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLAYBACK_ADDR ; 
 int /*<<< orphan*/  PLAYBACK_COUNT ; 
 int /*<<< orphan*/  PLAYBACK_SIZE ; 
 int /*<<< orphan*/  outb (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  outl (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  outw (unsigned int,scalar_t__) ; 
 int snd_pcm_lib_buffer_bytes (struct snd_pcm_substream*) ; 
 int snd_pcm_lib_period_bytes (struct snd_pcm_substream*) ; 
 struct snd_ice1712* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_vt1724_playback_pro_prepare(struct snd_pcm_substream *substream)
{
	struct snd_ice1712 *ice = snd_pcm_substream_chip(substream);
	unsigned char val;
	unsigned int size;

	spin_lock_irq(&ice->reg_lock);
	val = (8 - substream->runtime->channels) >> 1;
	outb(val, ICEMT1724(ice, BURST));

	outl(substream->runtime->dma_addr, ICEMT1724(ice, PLAYBACK_ADDR));

	size = (snd_pcm_lib_buffer_bytes(substream) >> 2) - 1;
	/* outl(size, ICEMT1724(ice, PLAYBACK_SIZE)); */
	outw(size, ICEMT1724(ice, PLAYBACK_SIZE));
	outb(size >> 16, ICEMT1724(ice, PLAYBACK_SIZE) + 2);
	size = (snd_pcm_lib_period_bytes(substream) >> 2) - 1;
	/* outl(size, ICEMT1724(ice, PLAYBACK_COUNT)); */
	outw(size, ICEMT1724(ice, PLAYBACK_COUNT));
	outb(size >> 16, ICEMT1724(ice, PLAYBACK_COUNT) + 2);

	spin_unlock_irq(&ice->reg_lock);

	/*
	printk(KERN_DEBUG "pro prepare: ch = %d, addr = 0x%x, "
	       "buffer = 0x%x, period = 0x%x\n",
	       substream->runtime->channels,
	       (unsigned int)substream->runtime->dma_addr,
	       snd_pcm_lib_buffer_bytes(substream),
	       snd_pcm_lib_period_bytes(substream));
	*/
	return 0;
}