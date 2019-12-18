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
typedef  int uint32_t ;
struct msmsdcc_host {scalar_t__ base; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 scalar_t__ MMCISTATUS ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int
msmsdcc_spin_on_status(struct msmsdcc_host *host, uint32_t mask, int maxspin)
{
	while (maxspin) {
		if ((readl(host->base + MMCISTATUS) & mask))
			return 0;
		udelay(1);
		--maxspin;
	}
	return -ETIMEDOUT;
}