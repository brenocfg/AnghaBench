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
struct res_common {int res_id; int /*<<< orphan*/  state; } ;
struct res_mtt {int order; struct res_common com; int /*<<< orphan*/  ref_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  RES_MTT_ALLOCATED ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct res_mtt* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct res_common *alloc_mtt_tr(int id, int order)
{
	struct res_mtt *ret;

	ret = kzalloc(sizeof *ret, GFP_KERNEL);
	if (!ret)
		return NULL;

	ret->com.res_id = id;
	ret->order = order;
	ret->com.state = RES_MTT_ALLOCATED;
	atomic_set(&ret->ref_count, 0);

	return &ret->com;
}