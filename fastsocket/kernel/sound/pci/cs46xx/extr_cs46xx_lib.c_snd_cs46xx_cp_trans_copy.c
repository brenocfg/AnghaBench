#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {scalar_t__ dma_area; } ;
struct snd_pcm_indirect {scalar_t__ hw_data; scalar_t__ sw_data; } ;
struct TYPE_3__ {scalar_t__ area; } ;
struct TYPE_4__ {TYPE_1__ hw_buf; } ;
struct snd_cs46xx {TYPE_2__ capt; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,size_t) ; 
 struct snd_cs46xx* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static void snd_cs46xx_cp_trans_copy(struct snd_pcm_substream *substream,
				     struct snd_pcm_indirect *rec, size_t bytes)
{
	struct snd_cs46xx *chip = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	memcpy(runtime->dma_area + rec->sw_data,
	       chip->capt.hw_buf.area + rec->hw_data, bytes);
}