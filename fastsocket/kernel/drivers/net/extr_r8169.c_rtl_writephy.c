#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  (* write ) (struct rtl8169_private*,int,int /*<<< orphan*/ ) ;} ;
struct rtl8169_private {TYPE_1__ mdio_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct rtl8169_private*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtl_writephy(struct rtl8169_private *tp, int location, u32 val)
{
	tp->mdio_ops.write(tp, location, val);
}