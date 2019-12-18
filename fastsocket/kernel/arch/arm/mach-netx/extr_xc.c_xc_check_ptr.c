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
struct xc {int /*<<< orphan*/  dev; int /*<<< orphan*/  no; } ;

/* Variables and functions */
 unsigned long NETX_PA_XMAC (int /*<<< orphan*/ ) ; 
 unsigned long NETX_PA_XPEC (int /*<<< orphan*/ ) ; 
 unsigned long XMAC_MEM_SIZE ; 
 unsigned long XPEC_MEM_SIZE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int xc_check_ptr(struct xc *x, unsigned long adr, unsigned int size)
{
	if (adr >= NETX_PA_XMAC(x->no) &&
	    adr + size < NETX_PA_XMAC(x->no) + XMAC_MEM_SIZE)
		return 0;

	if (adr >= NETX_PA_XPEC(x->no) &&
	    adr + size < NETX_PA_XPEC(x->no) + XPEC_MEM_SIZE)
		return 0;

	dev_err(x->dev, "Illegal pointer in firmware found. aborting\n");

	return -1;
}