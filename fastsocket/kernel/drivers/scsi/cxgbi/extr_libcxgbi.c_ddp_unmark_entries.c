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
struct cxgbi_ddp_info {int /*<<< orphan*/  map_lock; int /*<<< orphan*/ * gl_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void ddp_unmark_entries(struct cxgbi_ddp_info *ddp,
						int start, int count)
{
	spin_lock(&ddp->map_lock);
	memset(&ddp->gl_map[start], 0,
		count * sizeof(struct cxgbi_gather_list *));
	spin_unlock(&ddp->map_lock);
}