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
struct niu {int flags; } ;

/* Variables and functions */
 int BMAC_NUM_ALT_ADDR ; 
 int NIU_FLAGS_XMAC ; 
 int XMAC_NUM_ALT_ADDR ; 

__attribute__((used)) static int niu_num_alt_addr(struct niu *np)
{
	if (np->flags & NIU_FLAGS_XMAC)
		return XMAC_NUM_ALT_ADDR;
	else
		return BMAC_NUM_ALT_ADDR;
}