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
struct nouveau_namedb {int /*<<< orphan*/  lock; } ;
struct nouveau_handle {int dummy; } ;

/* Variables and functions */
 struct nouveau_handle* nouveau_namedb_lookup_cinst (struct nouveau_namedb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 

struct nouveau_handle *
nouveau_namedb_get_cinst(struct nouveau_namedb *namedb, u32 cinst)
{
	struct nouveau_handle *handle;
	read_lock(&namedb->lock);
	handle = nouveau_namedb_lookup_cinst(namedb, cinst);
	if (handle == NULL)
		read_unlock(&namedb->lock);
	return handle;
}