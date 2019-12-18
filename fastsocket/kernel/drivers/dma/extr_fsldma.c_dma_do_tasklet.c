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
struct fsl_dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fsl_chan_ld_cleanup (struct fsl_dma_chan*) ; 

__attribute__((used)) static void dma_do_tasklet(unsigned long data)
{
	struct fsl_dma_chan *fsl_chan = (struct fsl_dma_chan *)data;
	fsl_chan_ld_cleanup(fsl_chan);
}