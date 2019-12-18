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
 int CHCR_IE ; 
 int sh_dmae_readl (struct sh_dmae_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sh_dmae_writel (struct sh_dmae_chan*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dmae_start(struct sh_dmae_chan *sh_chan)
{
	u32 chcr = sh_dmae_readl(sh_chan, CHCR);

	chcr |= (CHCR_DE|CHCR_IE);
	sh_dmae_writel(sh_chan, chcr, CHCR);
}