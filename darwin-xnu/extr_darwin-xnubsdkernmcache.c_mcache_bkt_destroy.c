#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int mc_flags; scalar_t__ mc_purge_cnt; int /*<<< orphan*/  mc_private; int /*<<< orphan*/  (* mc_slab_free ) (int /*<<< orphan*/ ,TYPE_2__*,int) ;int /*<<< orphan*/  mc_name; } ;
typedef  TYPE_1__ mcache_t ;
struct TYPE_11__ {struct TYPE_11__* obj_next; } ;
typedef  TYPE_2__ mcache_obj_t ;
struct TYPE_12__ {int /*<<< orphan*/  bt_cache; } ;
typedef  TYPE_3__ mcache_bkttype_t ;
struct TYPE_13__ {TYPE_2__** bkt_obj; } ;
typedef  TYPE_4__ mcache_bkt_t ;

/* Variables and functions */
 int MCF_DEBUG ; 
 int /*<<< orphan*/  mcache_free (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ,void*,void*,int,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_2__*,int) ; 

__attribute__((used)) static void
mcache_bkt_destroy(mcache_t *cp, mcache_bkttype_t *btp, mcache_bkt_t *bkt,
    int nobjs)
{
	if (nobjs > 0) {
		mcache_obj_t *top = bkt->bkt_obj[nobjs - 1];

		if (cp->mc_flags & MCF_DEBUG) {
			mcache_obj_t *o = top;
			int cnt = 0;

			/*
			 * Verify that the chain of objects in the bucket is
			 * valid.  Any mismatch here means a mistake when the
			 * object(s) were freed to the CPU layer, so we panic.
			 */
			while (o != NULL) {
				o = o->obj_next;
				++cnt;
			}
			if (cnt != nobjs) {
				panic("mcache_bkt_destroy: %s cp %p corrupted "
				    "list in bkt %p (nobjs %d actual %d)\n",
				    cp->mc_name, (void *)cp, (void *)bkt,
				    nobjs, cnt);
			}
		}

		/* Advise the slab layer to purge the object(s) */
		(*cp->mc_slab_free)(cp->mc_private, top,
		    (cp->mc_flags & MCF_DEBUG) || cp->mc_purge_cnt);
	}
	mcache_free(btp->bt_cache, bkt);
}