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
struct rtl8169_private {int dummy; } ;
struct exgmac_reg {int /*<<< orphan*/  val; int /*<<< orphan*/  mask; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERIAR_EXGMAC ; 
 int /*<<< orphan*/  rtl_eri_write (struct rtl8169_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtl_write_exgmac_batch(struct rtl8169_private *tp,
				   const struct exgmac_reg *r, int len)
{
	while (len-- > 0) {
		rtl_eri_write(tp, r->addr, r->mask, r->val, ERIAR_EXGMAC);
		r++;
	}
}