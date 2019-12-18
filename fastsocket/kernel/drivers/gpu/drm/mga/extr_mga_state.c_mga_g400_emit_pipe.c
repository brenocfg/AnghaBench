#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int warp_pipe; } ;
typedef  TYPE_1__ drm_mga_sarea_t ;
struct TYPE_5__ {unsigned int warp_pipe; int* warp_pipe_phys; int wagp_enable; TYPE_1__* sarea_priv; } ;
typedef  TYPE_2__ drm_mga_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADVANCE_DMA () ; 
 int /*<<< orphan*/  BEGIN_DMA (int) ; 
 int /*<<< orphan*/  DMA_BLOCK (scalar_t__,int,scalar_t__,int,scalar_t__,int,scalar_t__,int) ; 
 int /*<<< orphan*/  DMA_LOCALS ; 
 scalar_t__ MGA_DMAPAD ; 
 int MGA_DUALTEX ; 
 scalar_t__ MGA_DWGCTL ; 
 int MGA_DWGCTL_FLUSH ; 
 scalar_t__ MGA_DWGSYNC ; 
 scalar_t__ MGA_EXEC ; 
 scalar_t__ MGA_FXLEFT ; 
 scalar_t__ MGA_FXRIGHT ; 
 int MGA_G400_TC2_MAGIC ; 
 int MGA_G400_WR56_MAGIC ; 
 int MGA_G400_WR_MAGIC ; 
 scalar_t__ MGA_LEN ; 
 unsigned int MGA_T2 ; 
 scalar_t__ MGA_TEXCTL2 ; 
 scalar_t__ MGA_WACCEPTSEQ ; 
 scalar_t__ MGA_WFLAG ; 
 scalar_t__ MGA_WFLAG1 ; 
 scalar_t__ MGA_WIADDR2 ; 
 int MGA_WMODE_START ; 
 int MGA_WMODE_SUSPEND ; 
 scalar_t__ MGA_WR49 ; 
 scalar_t__ MGA_WR52 ; 
 scalar_t__ MGA_WR53 ; 
 scalar_t__ MGA_WR54 ; 
 scalar_t__ MGA_WR56 ; 
 scalar_t__ MGA_WR57 ; 
 scalar_t__ MGA_WR60 ; 
 scalar_t__ MGA_WR61 ; 
 scalar_t__ MGA_WR62 ; 
 scalar_t__ MGA_WVRTXSZ ; 
 scalar_t__ MGA_YDST ; 

__attribute__((used)) static __inline__ void mga_g400_emit_pipe(drm_mga_private_t *dev_priv)
{
	drm_mga_sarea_t *sarea_priv = dev_priv->sarea_priv;
	unsigned int pipe = sarea_priv->warp_pipe;
	DMA_LOCALS;

/*	printk("mga_g400_emit_pipe %x\n", pipe); */

	BEGIN_DMA(10);

	DMA_BLOCK(MGA_WIADDR2, MGA_WMODE_SUSPEND,
		  MGA_DMAPAD, 0x00000000,
		  MGA_DMAPAD, 0x00000000, MGA_DMAPAD, 0x00000000);

	if (pipe & MGA_T2) {
		DMA_BLOCK(MGA_WVRTXSZ, 0x00001e09,
			  MGA_DMAPAD, 0x00000000,
			  MGA_DMAPAD, 0x00000000, MGA_DMAPAD, 0x00000000);

		DMA_BLOCK(MGA_WACCEPTSEQ, 0x00000000,
			  MGA_WACCEPTSEQ, 0x00000000,
			  MGA_WACCEPTSEQ, 0x00000000,
			  MGA_WACCEPTSEQ, 0x1e000000);
	} else {
		if (dev_priv->warp_pipe & MGA_T2) {
			/* Flush the WARP pipe */
			DMA_BLOCK(MGA_YDST, 0x00000000,
				  MGA_FXLEFT, 0x00000000,
				  MGA_FXRIGHT, 0x00000001,
				  MGA_DWGCTL, MGA_DWGCTL_FLUSH);

			DMA_BLOCK(MGA_LEN + MGA_EXEC, 0x00000001,
				  MGA_DWGSYNC, 0x00007000,
				  MGA_TEXCTL2, MGA_G400_TC2_MAGIC,
				  MGA_LEN + MGA_EXEC, 0x00000000);

			DMA_BLOCK(MGA_TEXCTL2, (MGA_DUALTEX |
						MGA_G400_TC2_MAGIC),
				  MGA_LEN + MGA_EXEC, 0x00000000,
				  MGA_TEXCTL2, MGA_G400_TC2_MAGIC,
				  MGA_DMAPAD, 0x00000000);
		}

		DMA_BLOCK(MGA_WVRTXSZ, 0x00001807,
			  MGA_DMAPAD, 0x00000000,
			  MGA_DMAPAD, 0x00000000, MGA_DMAPAD, 0x00000000);

		DMA_BLOCK(MGA_WACCEPTSEQ, 0x00000000,
			  MGA_WACCEPTSEQ, 0x00000000,
			  MGA_WACCEPTSEQ, 0x00000000,
			  MGA_WACCEPTSEQ, 0x18000000);
	}

	DMA_BLOCK(MGA_WFLAG, 0x00000000,
		  MGA_WFLAG1, 0x00000000,
		  MGA_WR56, MGA_G400_WR56_MAGIC, MGA_DMAPAD, 0x00000000);

	DMA_BLOCK(MGA_WR49, 0x00000000,	/* tex0              */
		  MGA_WR57, 0x00000000,	/* tex0              */
		  MGA_WR53, 0x00000000,	/* tex1              */
		  MGA_WR61, 0x00000000);	/* tex1              */

	DMA_BLOCK(MGA_WR54, MGA_G400_WR_MAGIC,	/* tex0 width        */
		  MGA_WR62, MGA_G400_WR_MAGIC,	/* tex0 height       */
		  MGA_WR52, MGA_G400_WR_MAGIC,	/* tex1 width        */
		  MGA_WR60, MGA_G400_WR_MAGIC);	/* tex1 height       */

	/* Padding required due to hardware bug */
	DMA_BLOCK(MGA_DMAPAD, 0xffffffff,
		  MGA_DMAPAD, 0xffffffff,
		  MGA_DMAPAD, 0xffffffff,
		  MGA_WIADDR2, (dev_priv->warp_pipe_phys[pipe] |
				MGA_WMODE_START | dev_priv->wagp_enable));

	ADVANCE_DMA();
}