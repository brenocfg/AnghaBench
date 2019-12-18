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
struct sa1111 {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ SA1111_SKCDR ; 
 unsigned int* opdiv_table ; 
 unsigned int sa1111_readl (scalar_t__) ; 

__attribute__((used)) static unsigned int __sa1111_pll_clock(struct sa1111 *sachip)
{
	unsigned int skcdr, fbdiv, ipdiv, opdiv;

	skcdr = sa1111_readl(sachip->base + SA1111_SKCDR);

	fbdiv = (skcdr & 0x007f) + 2;
	ipdiv = ((skcdr & 0x0f80) >> 7) + 2;
	opdiv = opdiv_table[(skcdr & 0x3000) >> 12];

	return 3686400 * fbdiv / (ipdiv * opdiv);
}