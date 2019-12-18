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
typedef  size_t u8 ;
struct ucc_geth_private {scalar_t__* indAddrRegUsed; } ;

/* Variables and functions */
 int hw_clear_addr_in_paddr (struct ucc_geth_private*,size_t) ; 

__attribute__((used)) static int ugeth_82xx_filtering_clear_addr_in_paddr(struct ucc_geth_private *ugeth,
						    u8 paddr_num)
{
	ugeth->indAddrRegUsed[paddr_num] = 0; /* mark this paddr as not used */
	return hw_clear_addr_in_paddr(ugeth, paddr_num);/* clear in hardware */
}