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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int (* flip ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  flip_data; } ;
struct nv10_software_chan {TYPE_1__ base; } ;
struct nouveau_object {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ nv_engctx (int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nv10_software_flip(struct nouveau_object *object, u32 mthd,
		   void *args, u32 size)
{
	struct nv10_software_chan *chan = (void *)nv_engctx(object->parent);
	if (chan->base.flip)
		return chan->base.flip(chan->base.flip_data);
	return -EINVAL;
}