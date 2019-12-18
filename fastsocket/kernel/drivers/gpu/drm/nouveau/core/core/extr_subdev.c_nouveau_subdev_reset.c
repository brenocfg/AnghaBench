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
struct nouveau_object {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* fini ) (struct nouveau_object*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  nv_debug (struct nouveau_object*,char*) ; 
 TYPE_1__* nv_ofuncs (struct nouveau_object*) ; 
 int /*<<< orphan*/  nv_trace (struct nouveau_object*,char*) ; 
 int /*<<< orphan*/  stub1 (struct nouveau_object*,int) ; 

void
nouveau_subdev_reset(struct nouveau_object *subdev)
{
	nv_trace(subdev, "resetting...\n");
	nv_ofuncs(subdev)->fini(subdev, false);
	nv_debug(subdev, "reset\n");
}