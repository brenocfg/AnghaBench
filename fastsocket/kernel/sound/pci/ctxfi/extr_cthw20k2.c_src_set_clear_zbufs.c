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
struct TYPE_3__ {int czbfs; } ;
struct TYPE_4__ {TYPE_1__ bf; } ;
struct src_rsc_ctrl_blk {TYPE_2__ dirty; } ;

/* Variables and functions */

__attribute__((used)) static int src_set_clear_zbufs(void *blk, unsigned int clear)
{
	((struct src_rsc_ctrl_blk *)blk)->dirty.bf.czbfs = (clear ? 1 : 0);
	return 0;
}