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
struct qib_pportdata {scalar_t__* sdma_head_dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  qib_sdma_7220_setlengen (struct qib_pportdata*) ; 
 int /*<<< orphan*/  qib_sdma_update_7220_tail (struct qib_pportdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qib_7220_sdma_hw_start_up(struct qib_pportdata *ppd)
{
	qib_sdma_7220_setlengen(ppd);
	qib_sdma_update_7220_tail(ppd, 0); /* Set SendDmaTail */
	ppd->sdma_head_dma[0] = 0;
}