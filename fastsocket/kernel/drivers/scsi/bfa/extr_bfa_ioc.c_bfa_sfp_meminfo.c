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
typedef  int /*<<< orphan*/  u32 ;
struct sfp_mem_s {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_DMA_ALIGN_SZ ; 
 int /*<<< orphan*/  BFA_ROUNDUP (int,int /*<<< orphan*/ ) ; 

u32
bfa_sfp_meminfo(void)
{
	return BFA_ROUNDUP(sizeof(struct sfp_mem_s), BFA_DMA_ALIGN_SZ);
}