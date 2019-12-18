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
struct sh_cmt_priv {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMCSR ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sh_cmt_start_stop_ch (struct sh_cmt_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sh_cmt_write (struct sh_cmt_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sh_cmt_disable(struct sh_cmt_priv *p)
{
	/* disable channel */
	sh_cmt_start_stop_ch(p, 0);

	/* disable interrupts in CMT block */
	sh_cmt_write(p, CMCSR, 0);

	/* stop clock */
	clk_disable(p->clk);
}