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
typedef  int u16 ;
struct i2o_message {int dummy; } ;
struct TYPE_3__ {TYPE_2__* virt; } ;
struct i2o_controller {scalar_t__ short_req; scalar_t__ pae_support; TYPE_1__ status_block; } ;
struct TYPE_4__ {int inbound_frame_size; } ;
typedef  TYPE_2__ i2o_status_block ;

/* Variables and functions */

u16 i2o_sg_tablesize(struct i2o_controller *c, u16 body_size)
{
	i2o_status_block *sb = c->status_block.virt;
	u16 sg_count =
	    (sb->inbound_frame_size - sizeof(struct i2o_message) / 4) -
	    body_size;

	if (c->pae_support) {
		/*
		 * for 64-bit a SG attribute element must be added and each
		 * SG element needs 12 bytes instead of 8.
		 */
		sg_count -= 2;
		sg_count /= 3;
	} else
		sg_count /= 2;

	if (c->short_req && (sg_count > 8))
		sg_count = 8;

	return sg_count;
}