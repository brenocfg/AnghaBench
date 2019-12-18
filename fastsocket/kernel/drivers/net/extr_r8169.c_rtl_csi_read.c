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
struct TYPE_2__ {int /*<<< orphan*/  (* read ) (struct rtl8169_private*,int) ;} ;
struct rtl8169_private {TYPE_1__ csi_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct rtl8169_private*,int) ; 

__attribute__((used)) static u32 rtl_csi_read(struct rtl8169_private *tp, int addr)
{
	return tp->csi_ops.read ? tp->csi_ops.read(tp, addr) : ~0;
}