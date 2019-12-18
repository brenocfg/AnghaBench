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
struct nouveau_object {int dummy; } ;
struct nouveau_fifo_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nouveau_fifo_channel_destroy (struct nouveau_fifo_chan*) ; 

void
_nouveau_fifo_channel_dtor(struct nouveau_object *object)
{
	struct nouveau_fifo_chan *chan = (void *)object;
	nouveau_fifo_channel_destroy(chan);
}