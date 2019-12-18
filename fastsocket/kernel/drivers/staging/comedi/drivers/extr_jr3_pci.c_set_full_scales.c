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
struct six_axis_t {int fx; int fy; int fz; int mx; int my; int mz; } ;
struct TYPE_2__ {int /*<<< orphan*/  mz; int /*<<< orphan*/  my; int /*<<< orphan*/  mx; int /*<<< orphan*/  fz; int /*<<< orphan*/  fy; int /*<<< orphan*/  fx; } ;
struct jr3_channel {int /*<<< orphan*/  command_word0; TYPE_1__ full_scale; } ;

/* Variables and functions */
 int /*<<< orphan*/  printk (char*,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  set_s16 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void set_full_scales(volatile struct jr3_channel *channel,
			    struct six_axis_t full_scale)
{
	printk("%d %d %d %d %d %d\n",
	       full_scale.fx,
	       full_scale.fy,
	       full_scale.fz, full_scale.mx, full_scale.my, full_scale.mz);
	set_s16(&channel->full_scale.fx, full_scale.fx);
	set_s16(&channel->full_scale.fy, full_scale.fy);
	set_s16(&channel->full_scale.fz, full_scale.fz);
	set_s16(&channel->full_scale.mx, full_scale.mx);
	set_s16(&channel->full_scale.my, full_scale.my);
	set_s16(&channel->full_scale.mz, full_scale.mz);
	set_s16(&channel->command_word0, 0x0a00);
}