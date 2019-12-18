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
struct TYPE_3__ {int arxctl; } ;
struct TYPE_4__ {TYPE_1__ bf; } ;
struct daio_mgr_ctrl_blk {TYPE_2__ dirty; int /*<<< orphan*/ * rxctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARXCTL_EN ; 
 int /*<<< orphan*/  set_field (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int daio_mgr_dsb_dai(void *blk, unsigned int idx)
{
	struct daio_mgr_ctrl_blk *ctl = blk;

	set_field(&ctl->rxctl[idx], ARXCTL_EN, 0);

	ctl->dirty.bf.arxctl |= (0x1 << idx);
	return 0;
}