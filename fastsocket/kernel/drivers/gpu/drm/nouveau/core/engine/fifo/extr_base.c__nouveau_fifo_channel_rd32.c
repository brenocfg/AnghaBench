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
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct nouveau_object {int dummy; } ;
struct nouveau_fifo_chan {scalar_t__ user; } ;

/* Variables and functions */
 int /*<<< orphan*/  ioread32_native (scalar_t__) ; 

u32
_nouveau_fifo_channel_rd32(struct nouveau_object *object, u64 addr)
{
	struct nouveau_fifo_chan *chan = (void *)object;
	return ioread32_native(chan->user + addr);
}