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
struct rtl_cond {int (* check ) (struct rtl8169_private*) ;int /*<<< orphan*/  msg; } ;
struct rtl8169_private {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  netif_err (struct rtl8169_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,unsigned int) ; 
 int stub1 (struct rtl8169_private*) ; 

__attribute__((used)) static bool rtl_loop_wait(struct rtl8169_private *tp, const struct rtl_cond *c,
			  void (*delay)(unsigned int), unsigned int d, int n,
			  bool high)
{
	int i;

	for (i = 0; i < n; i++) {
		delay(d);
		if (c->check(tp) == high)
			return true;
	}
	netif_err(tp, drv, tp->dev, "%s == %d (loop: %d, delay: %d).\n",
		  c->msg, !high, n, d);
	return false;
}