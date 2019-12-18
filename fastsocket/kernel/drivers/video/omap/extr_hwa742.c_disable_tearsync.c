#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_4__ {TYPE_1__* extif; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* enable_tearsync ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  HWA742_NDP_CTRL ; 
 TYPE_2__ hwa742 ; 
 int hwa742_read_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwa742_write_reg (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void disable_tearsync(void)
{
	u8 b;

	hwa742.extif->enable_tearsync(0, 0);

	b = hwa742_read_reg(HWA742_NDP_CTRL);
	b &= ~(1 << 2);
	hwa742_write_reg(HWA742_NDP_CTRL, b);
}