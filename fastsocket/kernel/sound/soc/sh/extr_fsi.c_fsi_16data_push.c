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
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct snd_pcm_runtime {scalar_t__ dma_area; } ;
struct fsi_priv {int byte_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  DODT ; 
 int /*<<< orphan*/  fsi_reg_write (struct fsi_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void fsi_16data_push(struct fsi_priv *fsi,
			   struct snd_pcm_runtime *runtime,
			   int send)
{
	u16 *dma_start;
	u32 snd;
	int i;

	/* get dma start position for FSI */
	dma_start = (u16 *)runtime->dma_area;
	dma_start += fsi->byte_offset / 2;

	/*
	 * soft dma
	 * FSI can not use DMA when 16bpp
	 */
	for (i = 0; i < send; i++) {
		snd = (u32)dma_start[i];
		fsi_reg_write(fsi, DODT, snd << 8);
	}
}