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
struct scatterlist {int dummy; } ;
struct dc390_srb {int /*<<< orphan*/  SGToBeXferLen; int /*<<< orphan*/  SGBusAddr; struct scatterlist* pSegmentList; } ;

/* Variables and functions */
 int /*<<< orphan*/  sg_dma_address (struct scatterlist*) ; 
 int /*<<< orphan*/  sg_dma_len (struct scatterlist*) ; 

__attribute__((used)) static void inline dc390_start_segment(struct dc390_srb* pSRB)
{
	struct scatterlist *psgl = pSRB->pSegmentList;

	/* start new sg segment */
	pSRB->SGBusAddr = sg_dma_address(psgl);
	pSRB->SGToBeXferLen = sg_dma_len(psgl);
}