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
struct pxa3xx_nand_info {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  NDSR ; 
 int NDSR_MASK ; 
 int WAIT_EVENT_TIMEOUT ; 
 int nand_readl (struct pxa3xx_nand_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nand_writel (struct pxa3xx_nand_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int wait_for_event(struct pxa3xx_nand_info *info, uint32_t event)
{
	int timeout = WAIT_EVENT_TIMEOUT;
	uint32_t ndsr;

	while (timeout--) {
		ndsr = nand_readl(info, NDSR) & NDSR_MASK;
		if (ndsr & event) {
			nand_writel(info, NDSR, ndsr);
			return 0;
		}
		udelay(10);
	}

	return -ETIMEDOUT;
}