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
struct cxgbi_gather_list {int dummy; } ;
struct cxgbi_ddp_info {int /*<<< orphan*/  map_lock; struct cxgbi_gather_list** gl_map; } ;

/* Variables and functions */
 int CXGBI_DBG_DDP ; 
 int EBUSY ; 
 int /*<<< orphan*/  log_debug (int,char*,unsigned int,...) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int ddp_find_unused_entries(struct cxgbi_ddp_info *ddp,
					unsigned int start, unsigned int max,
					unsigned int count,
					struct cxgbi_gather_list *gl)
{
	unsigned int i, j, k;

	/*  not enough entries */
	if ((max - start) < count) {
		log_debug(1 << CXGBI_DBG_DDP,
			"NOT enough entries %u+%u < %u.\n", start, count, max);
		return -EBUSY;
	}

	max -= count;
	spin_lock(&ddp->map_lock);
	for (i = start; i < max;) {
		for (j = 0, k = i; j < count; j++, k++) {
			if (ddp->gl_map[k])
				break;
		}
		if (j == count) {
			for (j = 0, k = i; j < count; j++, k++)
				ddp->gl_map[k] = gl;
			spin_unlock(&ddp->map_lock);
			return i;
		}
		i += j + 1;
	}
	spin_unlock(&ddp->map_lock);
	log_debug(1 << CXGBI_DBG_DDP,
		"NO suitable entries %u available.\n", count);
	return -EBUSY;
}