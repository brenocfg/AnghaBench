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
 int nouveau_engctx_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv_engctx (struct nouveau_object*) ; 

int
_nouveau_engctx_init(struct nouveau_object *object)
{
	return nouveau_engctx_init(nv_engctx(object));
}