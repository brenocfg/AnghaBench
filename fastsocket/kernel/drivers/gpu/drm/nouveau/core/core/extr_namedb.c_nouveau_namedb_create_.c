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
typedef  int u32 ;
struct nouveau_oclass {int dummy; } ;
struct nouveau_object {int dummy; } ;
struct nouveau_namedb {int /*<<< orphan*/  list; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int NV_NAMEDB_CLASS ; 
 int nouveau_parent_create_ (struct nouveau_object*,struct nouveau_object*,struct nouveau_oclass*,int,struct nouveau_oclass*,int,int,void**) ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 

int
nouveau_namedb_create_(struct nouveau_object *parent,
		       struct nouveau_object *engine,
		       struct nouveau_oclass *oclass, u32 pclass,
		       struct nouveau_oclass *sclass, u32 engcls,
		       int length, void **pobject)
{
	struct nouveau_namedb *namedb;
	int ret;

	ret = nouveau_parent_create_(parent, engine, oclass, pclass |
				     NV_NAMEDB_CLASS, sclass, engcls,
				     length, pobject);
	namedb = *pobject;
	if (ret)
		return ret;

	rwlock_init(&namedb->lock);
	INIT_LIST_HEAD(&namedb->list);
	return 0;
}