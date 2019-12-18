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
struct nouveau_object {scalar_t__ parent; } ;
struct nouveau_fifo_chan {int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ nv_engctx (scalar_t__) ; 

__attribute__((used)) static int
nv04_software_set_ref(struct nouveau_object *object, u32 mthd,
		      void *data, u32 size)
{
	struct nouveau_object *channel = (void *)nv_engctx(object->parent);
	struct nouveau_fifo_chan *fifo = (void *)channel->parent;
	atomic_set(&fifo->refcnt, *(u32*)data);
	return 0;
}