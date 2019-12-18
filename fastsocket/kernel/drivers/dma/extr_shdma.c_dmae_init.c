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
struct sh_dmae_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHCR ; 
 int /*<<< orphan*/  RS_DEFAULT ; 
 int /*<<< orphan*/  sh_dmae_writel (struct sh_dmae_chan*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dmae_init(struct sh_dmae_chan *sh_chan)
{
	u32 chcr = RS_DEFAULT; /* default is DUAL mode */
	sh_dmae_writel(sh_chan, chcr, CHCR);
}