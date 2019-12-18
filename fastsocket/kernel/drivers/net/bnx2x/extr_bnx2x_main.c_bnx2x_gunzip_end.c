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
struct bnx2x {int /*<<< orphan*/ * gunzip_buf; int /*<<< orphan*/  gunzip_mapping; TYPE_1__* pdev; TYPE_2__* strm; } ;
struct TYPE_4__ {int /*<<< orphan*/  workspace; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  FW_BUF_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnx2x_gunzip_end(struct bnx2x *bp)
{
	if (bp->strm) {
		vfree(bp->strm->workspace);
		kfree(bp->strm);
		bp->strm = NULL;
	}

	if (bp->gunzip_buf) {
		dma_free_coherent(&bp->pdev->dev, FW_BUF_SIZE, bp->gunzip_buf,
				  bp->gunzip_mapping);
		bp->gunzip_buf = NULL;
	}
}