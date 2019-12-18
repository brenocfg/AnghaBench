#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  line; } ;
struct mpsc_port_info {scalar_t__ sdma_base; TYPE_1__ port; } ;

/* Variables and functions */
 scalar_t__ SDMA_SDC ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void mpsc_sdma_burstsize(struct mpsc_port_info *pi, u32 burst_size)
{
	u32	v;

	pr_debug("mpsc_sdma_burstsize[%d]: burst_size: %d\n",
			pi->port.line, burst_size);

	burst_size >>= 3; /* Divide by 8 b/c reg values are 8-byte chunks */

	if (burst_size < 2)
		v = 0x0;	/* 1 64-bit word */
	else if (burst_size < 4)
		v = 0x1;	/* 2 64-bit words */
	else if (burst_size < 8)
		v = 0x2;	/* 4 64-bit words */
	else
		v = 0x3;	/* 8 64-bit words */

	writel((readl(pi->sdma_base + SDMA_SDC) & (0x3 << 12)) | (v << 12),
		pi->sdma_base + SDMA_SDC);
}