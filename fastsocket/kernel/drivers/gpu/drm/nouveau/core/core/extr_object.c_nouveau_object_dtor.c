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
struct TYPE_2__ {int /*<<< orphan*/  (* dtor ) (struct nouveau_object*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  nv_debug (struct nouveau_object*,char*) ; 
 TYPE_1__* nv_ofuncs (struct nouveau_object*) ; 
 int /*<<< orphan*/  stub1 (struct nouveau_object*) ; 

__attribute__((used)) static void
nouveau_object_dtor(struct nouveau_object *object)
{
	nv_debug(object, "destroying\n");
	nv_ofuncs(object)->dtor(object);
}