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
typedef  int /*<<< orphan*/  u16 ;
struct rtl8169_private {int dummy; } ;

/* Variables and functions */
 int ocp_read (struct rtl8169_private*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8168_get_ocp_reg (struct rtl8169_private*) ; 

__attribute__((used)) static int r8168dp_check_dash(struct rtl8169_private *tp)
{
	u16 reg = rtl8168_get_ocp_reg(tp);

	return (ocp_read(tp, 0x0f, reg) & 0x00008000) ? 1 : 0;
}