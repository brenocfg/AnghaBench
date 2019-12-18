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
struct isp1362_hcd {int /*<<< orphan*/  stat1; int /*<<< orphan*/  stat2; int /*<<< orphan*/  stat4; int /*<<< orphan*/  stat8; int /*<<< orphan*/  stat16; } ;

/* Variables and functions */

__attribute__((used)) static inline void ALIGNSTAT(struct isp1362_hcd *isp1362_hcd, void *ptr)
{
	unsigned long p = (unsigned long)ptr;
	if (!(p & 0xf))
		isp1362_hcd->stat16++;
	else if (!(p & 0x7))
		isp1362_hcd->stat8++;
	else if (!(p & 0x3))
		isp1362_hcd->stat4++;
	else if (!(p & 0x1))
		isp1362_hcd->stat2++;
	else
		isp1362_hcd->stat1++;
}