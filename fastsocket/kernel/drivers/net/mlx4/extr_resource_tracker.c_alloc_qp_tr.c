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
struct res_qp {int local_qpn; struct res_common com; int /*<<< orphan*/  ref_count; int /*<<< orphan*/  mcg_spl; int /*<<< orphan*/  mcg_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RES_QP_RESERVED ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct res_qp* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct res_common *alloc_qp_tr(int id)
{
	struct res_qp *ret;

	ret = kzalloc(sizeof *ret, GFP_KERNEL);
	if (!ret)
		return NULL;

	ret->com.res_id = id;
	ret->com.state = RES_QP_RESERVED;
	ret->local_qpn = id;
	INIT_LIST_HEAD(&ret->mcg_list);
	spin_lock_init(&ret->mcg_spl);
	atomic_set(&ret->ref_count, 0);

	return &ret->com;
}