#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int srcimap; } ;
struct TYPE_6__ {TYPE_2__ bf; } ;
struct TYPE_4__ {int /*<<< orphan*/  srcaim; } ;
struct srcimp_mgr_ctrl_blk {TYPE_3__ dirty; TYPE_1__ srcimap; } ;

/* Variables and functions */
 int /*<<< orphan*/  SRCAIM_ARC ; 
 int /*<<< orphan*/  set_field (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int srcimp_mgr_set_imaparc(void *blk, unsigned int slot)
{
	struct srcimp_mgr_ctrl_blk *ctl = blk;

	set_field(&ctl->srcimap.srcaim, SRCAIM_ARC, slot);
	ctl->dirty.bf.srcimap = 1;
	return 0;
}