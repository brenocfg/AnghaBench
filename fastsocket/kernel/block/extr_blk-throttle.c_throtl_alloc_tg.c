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
struct throtl_grp {int /*<<< orphan*/  blkg; } ;
struct throtl_data {TYPE_1__* queue; } ;
struct TYPE_2__ {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int blkio_alloc_blkg_stats (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct throtl_grp*) ; 
 struct throtl_grp* kzalloc_node (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  throtl_init_group (struct throtl_grp*) ; 

__attribute__((used)) static struct throtl_grp *throtl_alloc_tg(struct throtl_data *td)
{
	struct throtl_grp *tg = NULL;
	int ret;

	tg = kzalloc_node(sizeof(*tg), GFP_ATOMIC, td->queue->node);
	if (!tg)
		return NULL;

	ret = blkio_alloc_blkg_stats(&tg->blkg);

	if (ret) {
		kfree(tg);
		return NULL;
	}

	throtl_init_group(tg);
	return tg;
}