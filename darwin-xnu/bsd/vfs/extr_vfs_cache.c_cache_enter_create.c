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
typedef  int /*<<< orphan*/  vnode_t ;
struct componentname {scalar_t__ cn_hash; int /*<<< orphan*/  cn_namelen; int /*<<< orphan*/  cn_nameptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  NAME_CACHE_LOCK () ; 
 int /*<<< orphan*/  NAME_CACHE_UNLOCK () ; 
 int /*<<< orphan*/  TRUE ; 
 char* add_name_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cache_enter_locked (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct componentname*,char const*) ; 
 scalar_t__ hash_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

const char *
cache_enter_create(vnode_t dvp, vnode_t vp, struct componentname *cnp)
{
	const char *strname;

        if (cnp->cn_hash == 0)
	        cnp->cn_hash = hash_string(cnp->cn_nameptr, cnp->cn_namelen);

	/*
	 * grab 2 references on the string entered
	 * one for the cache_enter_locked to consume
	 * and the second to be consumed by v_name (vnode_create call point)
	 */
	strname = add_name_internal(cnp->cn_nameptr, cnp->cn_namelen, cnp->cn_hash, TRUE, 0);

	NAME_CACHE_LOCK();

	cache_enter_locked(dvp, vp, cnp, strname);

	NAME_CACHE_UNLOCK();

	return (strname);
}