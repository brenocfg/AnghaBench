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

/* Variables and functions */
 int nouveau_gpuobj_fini (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nv_gpuobj (struct nouveau_object*) ; 

int
_nouveau_gpuobj_fini(struct nouveau_object *object, bool suspend)
{
	return nouveau_gpuobj_fini(nv_gpuobj(object), suspend);
}