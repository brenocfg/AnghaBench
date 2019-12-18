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
typedef  scalar_t__ u32 ;
struct pohmelfs_name {scalar_t__ hash; } ;
struct pohmelfs_inode {int dummy; } ;

/* Variables and functions */
 struct pohmelfs_name* pohmelfs_search_hash_unprecise (struct pohmelfs_inode*,scalar_t__) ; 

struct pohmelfs_name *pohmelfs_search_hash(struct pohmelfs_inode *pi, u32 hash)
{
	struct pohmelfs_name *tmp;

	tmp = pohmelfs_search_hash_unprecise(pi, hash);
	if (tmp && (tmp->hash == hash))
		return tmp;

	return NULL;
}