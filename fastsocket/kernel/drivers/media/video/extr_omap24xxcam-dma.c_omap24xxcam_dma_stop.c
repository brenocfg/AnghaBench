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
typedef  int /*<<< orphan*/  u32 ;
struct omap24xxcam_dma {int /*<<< orphan*/  dma_stop; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  omap24xxcam_dma_abort (struct omap24xxcam_dma*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void omap24xxcam_dma_stop(struct omap24xxcam_dma *dma, u32 csr)
{
	atomic_inc(&dma->dma_stop);
	omap24xxcam_dma_abort(dma, csr);
	atomic_dec(&dma->dma_stop);
}