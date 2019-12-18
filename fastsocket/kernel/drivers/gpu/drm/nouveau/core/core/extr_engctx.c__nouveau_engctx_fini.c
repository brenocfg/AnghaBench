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
 int nouveau_engctx_fini (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nv_engctx (struct nouveau_object*) ; 

int
_nouveau_engctx_fini(struct nouveau_object *object, bool suspend)
{
	return nouveau_engctx_fini(nv_engctx(object), suspend);
}