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
struct xc {scalar_t__ xpec_base; } ;

/* Variables and functions */
 scalar_t__ NETX_XPEC_PC_OFS ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

int xc_reset(struct xc *x)
{
	writel(0, x->xpec_base + NETX_XPEC_PC_OFS);
	return 0;
}