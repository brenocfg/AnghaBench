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
typedef  int u64 ;
struct be_eth_wrb {int frag_pa_lo; int frag_len; scalar_t__ rsvd0; int /*<<< orphan*/  frag_pa_hi; } ;

/* Variables and functions */
 int ETH_WRB_FRAG_LEN_MASK ; 
 int /*<<< orphan*/  upper_32_bits (int) ; 

__attribute__((used)) static inline void wrb_fill(struct be_eth_wrb *wrb, u64 addr, int len)
{
	wrb->frag_pa_hi = upper_32_bits(addr);
	wrb->frag_pa_lo = addr & 0xFFFFFFFF;
	wrb->frag_len = len & ETH_WRB_FRAG_LEN_MASK;
	wrb->rsvd0 = 0;
}