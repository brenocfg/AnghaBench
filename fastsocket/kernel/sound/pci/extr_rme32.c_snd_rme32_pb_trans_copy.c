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
struct snd_pcm_indirect {scalar_t__ sw_data; scalar_t__ hw_data; } ;
struct rme32 {scalar_t__ iobase; } ;
struct TYPE_2__ {scalar_t__ dma_area; } ;

/* Variables and functions */
 scalar_t__ RME32_IO_DATA_BUFFER ; 
 int /*<<< orphan*/  memcpy_toio (scalar_t__,scalar_t__,size_t) ; 
 struct rme32* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static void snd_rme32_pb_trans_copy(struct snd_pcm_substream *substream,
				    struct snd_pcm_indirect *rec, size_t bytes)
{
	struct rme32 *rme32 = snd_pcm_substream_chip(substream);
	memcpy_toio(rme32->iobase + RME32_IO_DATA_BUFFER + rec->hw_data,
		    substream->runtime->dma_area + rec->sw_data, bytes);
}