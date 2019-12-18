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
struct s3c24xx_dma_map {int* channels; } ;
struct s3c2410_dma_chan {scalar_t__ regs; } ;

/* Variables and functions */
 int S3C2443_DMAREQSEL_HW ; 
 scalar_t__ S3C2443_DMA_DMAREQSEL ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void s3c2443_dma_select(struct s3c2410_dma_chan *chan,
			       struct s3c24xx_dma_map *map)
{
	writel(map->channels[0] | S3C2443_DMAREQSEL_HW,
	       chan->regs + S3C2443_DMA_DMAREQSEL);
}