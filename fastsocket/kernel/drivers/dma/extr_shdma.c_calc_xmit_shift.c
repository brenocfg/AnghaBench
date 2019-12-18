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
typedef  size_t u32 ;
struct sh_dmae_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHCR ; 
 size_t CHCR_TS_MASK ; 
 size_t CHCR_TS_SHIFT ; 
 size_t sh_dmae_readl (struct sh_dmae_chan*,int /*<<< orphan*/ ) ; 
 unsigned int* ts_shift ; 

__attribute__((used)) static inline unsigned int calc_xmit_shift(struct sh_dmae_chan *sh_chan)
{
	u32 chcr = sh_dmae_readl(sh_chan, CHCR);
	return ts_shift[(chcr & CHCR_TS_MASK) >> CHCR_TS_SHIFT];
}