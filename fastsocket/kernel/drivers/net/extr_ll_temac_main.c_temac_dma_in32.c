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
struct temac_local {int /*<<< orphan*/  sdma_dcrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  dcr_read (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u32 temac_dma_in32(struct temac_local *lp, int reg)
{
	return dcr_read(lp->sdma_dcrs, reg);
}