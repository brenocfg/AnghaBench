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
struct s3c24xx_dma_order_ch {size_t* list; int flags; } ;
struct s3c24xx_dma_map {size_t* channels; } ;
struct s3c2410_dma_chan {scalar_t__ in_use; int req_ch; struct s3c24xx_dma_map* map; } ;
struct TYPE_4__ {struct s3c24xx_dma_order_ch* channels; } ;
struct TYPE_3__ {int map_size; int /*<<< orphan*/  (* select ) (struct s3c2410_dma_chan*,struct s3c24xx_dma_map*) ;struct s3c24xx_dma_map* map; } ;

/* Variables and functions */
 int DMA_CH_NEVER ; 
 int DMA_CH_VALID ; 
 int dma_channels ; 
 TYPE_2__* dma_order ; 
 TYPE_1__ dma_sel ; 
 int /*<<< orphan*/  is_channel_valid (size_t) ; 
 int /*<<< orphan*/  printk (char*,int,int) ; 
 struct s3c2410_dma_chan* s3c2410_chans ; 
 struct s3c2410_dma_chan** s3c_dma_chan_map ; 
 int /*<<< orphan*/  stub1 (struct s3c2410_dma_chan*,struct s3c24xx_dma_map*) ; 

__attribute__((used)) static struct s3c2410_dma_chan *s3c2410_dma_map_channel(int channel)
{
	struct s3c24xx_dma_order_ch *ord = NULL;
	struct s3c24xx_dma_map *ch_map;
	struct s3c2410_dma_chan *dmach;
	int ch;

	if (dma_sel.map == NULL || channel > dma_sel.map_size)
		return NULL;

	ch_map = dma_sel.map + channel;

	/* first, try the board mapping */

	if (dma_order) {
		ord = &dma_order->channels[channel];

		for (ch = 0; ch < dma_channels; ch++) {
			if (!is_channel_valid(ord->list[ch]))
				continue;

			if (s3c2410_chans[ord->list[ch]].in_use == 0) {
				ch = ord->list[ch] & ~DMA_CH_VALID;
				goto found;
			}
		}

		if (ord->flags & DMA_CH_NEVER)
			return NULL;
	}

	/* second, search the channel map for first free */

	for (ch = 0; ch < dma_channels; ch++) {
		if (!is_channel_valid(ch_map->channels[ch]))
			continue;

		if (s3c2410_chans[ch].in_use == 0) {
			printk("mapped channel %d to %d\n", channel, ch);
			break;
		}
	}

	if (ch >= dma_channels)
		return NULL;

	/* update our channel mapping */

 found:
	dmach = &s3c2410_chans[ch];
	dmach->map = ch_map;
	dmach->req_ch = channel;
	s3c_dma_chan_map[channel] = dmach;

	/* select the channel */

	(dma_sel.select)(dmach, ch_map);

	return dmach;
}