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
struct s3c24xx_dma_map {unsigned long* channels_rx; unsigned long* channels; } ;
struct s3c2410_dma_chan {scalar_t__ regs; } ;
typedef  enum s3c2410_dmasrc { ____Placeholder_s3c2410_dmasrc } s3c2410_dmasrc ;

/* Variables and functions */
 unsigned long DMA_CH_VALID ; 
 int S3C2410_DMASRC_HW ; 
 unsigned long S3C2412_DMAREQSEL_HW ; 
 scalar_t__ S3C2412_DMA_DMAREQSEL ; 
 int /*<<< orphan*/  writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static void s3c2412_dma_direction(struct s3c2410_dma_chan *chan,
				  struct s3c24xx_dma_map *map,
				  enum s3c2410_dmasrc dir)
{
	unsigned long chsel;

	if (dir == S3C2410_DMASRC_HW)
		chsel = map->channels_rx[0];
	else
		chsel = map->channels[0];

	chsel &= ~DMA_CH_VALID;
	chsel |= S3C2412_DMAREQSEL_HW;

	writel(chsel, chan->regs + S3C2412_DMA_DMAREQSEL);
}