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
struct TYPE_3__ {int atxcsl; } ;
struct TYPE_4__ {TYPE_1__ bf; } ;
struct dao_ctrl_blk {unsigned int atxcsl; TYPE_2__ dirty; } ;

/* Variables and functions */

__attribute__((used)) static int dao_set_spos(void *blk, unsigned int spos)
{
	((struct dao_ctrl_blk *)blk)->atxcsl = spos;
	((struct dao_ctrl_blk *)blk)->dirty.bf.atxcsl = 1;
	return 0;
}