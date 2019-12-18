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
typedef  int u32 ;
struct sh_dmae_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHCR ; 
 int CHCR_DE ; 
 int CHCR_TE ; 
 int EBUSY ; 
 int sh_dmae_readl (struct sh_dmae_chan*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dmae_is_idle(struct sh_dmae_chan *sh_chan)
{
	u32 chcr = sh_dmae_readl(sh_chan, CHCR);
	if (chcr & CHCR_DE) {
		if (!(chcr & CHCR_TE))
			return -EBUSY; /* working */
	}
	return 0; /* waiting */
}