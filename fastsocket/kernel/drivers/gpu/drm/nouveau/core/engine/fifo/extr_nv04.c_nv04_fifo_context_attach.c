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
struct nouveau_object {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  chid; } ;
struct TYPE_3__ {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 TYPE_2__* nouveau_fifo_chan (struct nouveau_object*) ; 
 TYPE_1__* nv_engctx (struct nouveau_object*) ; 

int
nv04_fifo_context_attach(struct nouveau_object *parent,
			 struct nouveau_object *object)
{
	nv_engctx(object)->addr = nouveau_fifo_chan(parent)->chid;
	return 0;
}