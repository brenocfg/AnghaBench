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

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_NC_HASH ; 
 int /*<<< orphan*/  MAX (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  M_CACHE ; 
 int NUM_STRCACHE_LOCKS ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int desiredNegNodes ; 
 int desiredNodes ; 
 int desiredvnodes ; 
 int /*<<< orphan*/  hashinit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_crc32 () ; 
 int /*<<< orphan*/  init_string_table () ; 
 int /*<<< orphan*/  lck_attr_alloc_init () ; 
 int /*<<< orphan*/  lck_grp_alloc_init (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_grp_attr_alloc_init () ; 
 int /*<<< orphan*/  lck_mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* lck_rw_alloc_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  namecache_lck_attr ; 
 int /*<<< orphan*/  namecache_lck_grp ; 
 int /*<<< orphan*/  namecache_lck_grp_attr ; 
 void* namecache_rw_lock ; 
 int /*<<< orphan*/  nchash ; 
 int /*<<< orphan*/  nchashmask ; 
 int /*<<< orphan*/  nchashtbl ; 
 int /*<<< orphan*/  nchead ; 
 int /*<<< orphan*/  neghead ; 
 int /*<<< orphan*/  strcache_lck_attr ; 
 int /*<<< orphan*/  strcache_lck_grp ; 
 int /*<<< orphan*/  strcache_lck_grp_attr ; 
 int /*<<< orphan*/ * strcache_mtx_locks ; 
 void* strtable_rw_lock ; 

void
nchinit(void)
{
	int	i;

	desiredNegNodes = (desiredvnodes / 10);
	desiredNodes = desiredvnodes + desiredNegNodes;

	TAILQ_INIT(&nchead);
	TAILQ_INIT(&neghead);

	init_crc32();

	nchashtbl = hashinit(MAX(CONFIG_NC_HASH, (2 *desiredNodes)), M_CACHE, &nchash);
	nchashmask = nchash;
	nchash++;

	init_string_table();
	
	/* Allocate name cache lock group attribute and group */
	namecache_lck_grp_attr= lck_grp_attr_alloc_init();

	namecache_lck_grp = lck_grp_alloc_init("Name Cache",  namecache_lck_grp_attr);
	
	/* Allocate name cache lock attribute */
	namecache_lck_attr = lck_attr_alloc_init();

	/* Allocate name cache lock */
	namecache_rw_lock = lck_rw_alloc_init(namecache_lck_grp, namecache_lck_attr);


	/* Allocate string cache lock group attribute and group */
	strcache_lck_grp_attr= lck_grp_attr_alloc_init();

	strcache_lck_grp = lck_grp_alloc_init("String Cache",  strcache_lck_grp_attr);
	
	/* Allocate string cache lock attribute */
	strcache_lck_attr = lck_attr_alloc_init();

	/* Allocate string cache lock */
	strtable_rw_lock = lck_rw_alloc_init(strcache_lck_grp, strcache_lck_attr);

	for (i = 0; i < NUM_STRCACHE_LOCKS; i++)
		lck_mtx_init(&strcache_mtx_locks[i], strcache_lck_grp, strcache_lck_attr);
}