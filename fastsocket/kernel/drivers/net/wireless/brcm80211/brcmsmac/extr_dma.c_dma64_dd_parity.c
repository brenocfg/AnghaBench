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
struct dma64desc {int addrlow; int addrhigh; int ctrl1; int ctrl2; } ;

/* Variables and functions */
 int parity32 (int) ; 

__attribute__((used)) static bool dma64_dd_parity(struct dma64desc *dd)
{
	return parity32(dd->addrlow ^ dd->addrhigh ^ dd->ctrl1 ^ dd->ctrl2);
}