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
struct TYPE_2__ {scalar_t__ full_duplex; } ;
struct ioc3_private {int /*<<< orphan*/  emcr; TYPE_1__ mii; struct ioc3* regs; } ;
struct ioc3 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMCR_DUPLEX ; 
 int /*<<< orphan*/  ETCSR_FD ; 
 int /*<<< orphan*/  ETCSR_HD ; 
 int /*<<< orphan*/  ioc3_w_emcr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioc3_w_etcsr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ioc3_setup_duplex(struct ioc3_private *ip)
{
	struct ioc3 *ioc3 = ip->regs;

	if (ip->mii.full_duplex) {
		ioc3_w_etcsr(ETCSR_FD);
		ip->emcr |= EMCR_DUPLEX;
	} else {
		ioc3_w_etcsr(ETCSR_HD);
		ip->emcr &= ~EMCR_DUPLEX;
	}
	ioc3_w_emcr(ip->emcr);
}