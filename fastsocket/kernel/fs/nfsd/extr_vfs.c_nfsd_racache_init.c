#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct raparms {struct raparms* p_next; } ;
struct TYPE_4__ {int ra_size; } ;
struct TYPE_3__ {struct raparms* pb_head; int /*<<< orphan*/  pb_lock; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int RAPARM_HASH_SIZE ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 
 struct raparms* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsd_racache_shutdown () ; 
 TYPE_2__ nfsdstats ; 
 TYPE_1__* raparm_hash ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int
nfsd_racache_init(int cache_size)
{
	int	i;
	int	j = 0;
	int	nperbucket;
	struct raparms **raparm = NULL;


	if (raparm_hash[0].pb_head)
		return 0;
	nperbucket = DIV_ROUND_UP(cache_size, RAPARM_HASH_SIZE);
	if (nperbucket < 2)
		nperbucket = 2;
	cache_size = nperbucket * RAPARM_HASH_SIZE;

	dprintk("nfsd: allocating %d readahead buffers.\n", cache_size);

	for (i = 0; i < RAPARM_HASH_SIZE; i++) {
		spin_lock_init(&raparm_hash[i].pb_lock);

		raparm = &raparm_hash[i].pb_head;
		for (j = 0; j < nperbucket; j++) {
			*raparm = kzalloc(sizeof(struct raparms), GFP_KERNEL);
			if (!*raparm)
				goto out_nomem;
			raparm = &(*raparm)->p_next;
		}
		*raparm = NULL;
	}

	nfsdstats.ra_size = cache_size;
	return 0;

out_nomem:
	dprintk("nfsd: kmalloc failed, freeing readahead buffers\n");
	nfsd_racache_shutdown();
	return -ENOMEM;
}