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
typedef  size_t uint32_t ;
typedef  size_t u_long ;
struct nchashhead {struct namecache* lh_first; } ;
struct TYPE_2__ {struct namecache* le_next; } ;
struct namecache {size_t nc_hashval; TYPE_1__ nc_hash; int /*<<< orphan*/  nc_dvp; int /*<<< orphan*/  nc_name; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FREE (struct nchashhead*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (struct nchashhead*,struct namecache*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_CACHE ; 
 int /*<<< orphan*/  NAME_CACHE_LOCK () ; 
 int /*<<< orphan*/  NAME_CACHE_UNLOCK () ; 
 struct nchashhead* NCHHASH (int /*<<< orphan*/ ,size_t) ; 
 int desiredNegNodes ; 
 int desiredNodes ; 
 size_t hash_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nchashhead* hashinit (int,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  nc_hash ; 
 size_t nchash ; 
 size_t nchashmask ; 
 struct nchashhead* nchashtbl ; 
 scalar_t__ os_mul_overflow (int,int,int*) ; 

int
resize_namecache(int newsize)
{
    struct nchashhead	*new_table;
    struct nchashhead	*old_table;
    struct nchashhead	*old_head, *head;
    struct namecache 	*entry, *next;
    uint32_t		i, hashval;
    int			dNodes, dNegNodes, nelements;
    u_long		new_size, old_size;

    if (newsize < 0)
        return EINVAL;

    dNegNodes = (newsize / 10);
    dNodes = newsize + dNegNodes;
    // we don't support shrinking yet
    if (dNodes <= desiredNodes) {
        return 0;
    }

    if (os_mul_overflow(dNodes, 2, &nelements)) {
        return EINVAL;
    }

    new_table = hashinit(nelements, M_CACHE, &nchashmask);
    new_size  = nchashmask + 1;

    if (new_table == NULL) {
        return ENOMEM;
    }

    NAME_CACHE_LOCK();
    // do the switch!
    old_table = nchashtbl;
    nchashtbl = new_table;
    old_size  = nchash;
    nchash    = new_size;

    // walk the old table and insert all the entries into
    // the new table
    //
    for(i=0; i < old_size; i++) {
	old_head = &old_table[i];
	for (entry=old_head->lh_first; entry != NULL; entry=next) {
	    //
	    // XXXdbg - Beware: this assumes that hash_string() does
	    //                  the same thing as what happens in
	    //                  lookup() over in vfs_lookup.c
	    hashval = hash_string(entry->nc_name, 0);
	    entry->nc_hashval = hashval;
	    head = NCHHASH(entry->nc_dvp, hashval);
	    
	    next = entry->nc_hash.le_next;
	    LIST_INSERT_HEAD(head, entry, nc_hash);
	}
    }
    desiredNodes = dNodes;
    desiredNegNodes = dNegNodes;
    
    NAME_CACHE_UNLOCK();
    FREE(old_table, M_CACHE);

    return 0;
}