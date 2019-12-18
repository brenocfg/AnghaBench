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
struct nouveau_object {int dummy; } ;
struct nouveau_namedb {int dummy; } ;
struct nouveau_handle {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NV_NAMEDB_CLASS ; 
 struct nouveau_handle* nouveau_namedb_get_cinst (struct nouveau_namedb*,int /*<<< orphan*/ ) ; 
 scalar_t__ nv_pclass (struct nouveau_object*,int /*<<< orphan*/ ) ; 

struct nouveau_handle *
nouveau_handle_get_cinst(struct nouveau_object *engctx, u32 cinst)
{
	struct nouveau_namedb *namedb;
	if (engctx && (namedb = (void *)nv_pclass(engctx, NV_NAMEDB_CLASS)))
		return nouveau_namedb_get_cinst(namedb, cinst);
	return NULL;
}