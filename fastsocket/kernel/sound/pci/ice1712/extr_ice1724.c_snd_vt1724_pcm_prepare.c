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
struct vt1724_pcm_reg {scalar_t__ count; scalar_t__ size; scalar_t__ addr; } ;
struct snd_pcm_substream {TYPE_1__* runtime; } ;
struct snd_ice1712 {int /*<<< orphan*/  reg_lock; scalar_t__ profi_port; } ;
struct TYPE_2__ {int /*<<< orphan*/  dma_addr; struct vt1724_pcm_reg* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  outl (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 
 int snd_pcm_lib_buffer_bytes (struct snd_pcm_substream*) ; 
 int snd_pcm_lib_period_bytes (struct snd_pcm_substream*) ; 
 struct snd_ice1712* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_vt1724_pcm_prepare(struct snd_pcm_substream *substream)
{
	struct snd_ice1712 *ice = snd_pcm_substream_chip(substream);
	const struct vt1724_pcm_reg *reg = substream->runtime->private_data;

	spin_lock_irq(&ice->reg_lock);
	outl(substream->runtime->dma_addr, ice->profi_port + reg->addr);
	outw((snd_pcm_lib_buffer_bytes(substream) >> 2) - 1,
	     ice->profi_port + reg->size);
	outw((snd_pcm_lib_period_bytes(substream) >> 2) - 1,
	     ice->profi_port + reg->count);
	spin_unlock_irq(&ice->reg_lock);
	return 0;
}