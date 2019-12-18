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
typedef  int /*<<< orphan*/  u32 ;
struct nouveau_fifo_chan {int /*<<< orphan*/  refcnt; } ;
struct nouveau_channel {scalar_t__ object; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32
nv04_fence_read(struct nouveau_channel *chan)
{
	struct nouveau_fifo_chan *fifo = (void *)chan->object;
	return atomic_read(&fifo->refcnt);
}