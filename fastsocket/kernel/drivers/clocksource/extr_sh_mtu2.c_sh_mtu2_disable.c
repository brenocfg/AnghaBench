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
struct sh_mtu2_priv {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sh_mtu2_start_stop_ch (struct sh_mtu2_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sh_mtu2_disable(struct sh_mtu2_priv *p)
{
	/* disable channel */
	sh_mtu2_start_stop_ch(p, 0);

	/* stop clock */
	clk_disable(p->clk);
}