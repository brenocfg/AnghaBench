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
struct nouveau_oclass {int dummy; } ;
struct nouveau_object {int dummy; } ;
struct nouveau_namedb {int dummy; } ;

/* Variables and functions */
 int nouveau_namedb_create (struct nouveau_object*,struct nouveau_object*,struct nouveau_oclass*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct nouveau_namedb**) ; 
 struct nouveau_object* nv_object (struct nouveau_namedb*) ; 

int
_nouveau_namedb_ctor(struct nouveau_object *parent,
		     struct nouveau_object *engine,
		     struct nouveau_oclass *oclass, void *data, u32 size,
		     struct nouveau_object **pobject)
{
	struct nouveau_namedb *object;
	int ret;

	ret = nouveau_namedb_create(parent, engine, oclass, 0, NULL, 0, &object);
	*pobject = nv_object(object);
	if (ret)
		return ret;

	return 0;
}