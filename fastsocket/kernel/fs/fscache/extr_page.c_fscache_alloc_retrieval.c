#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned long flags; int /*<<< orphan*/  fast_work; } ;
struct fscache_retrieval {TYPE_1__ op; int /*<<< orphan*/  to_do; int /*<<< orphan*/  start_time; void* context; int /*<<< orphan*/  end_io_func; struct address_space* mapping; } ;
struct fscache_cookie {int /*<<< orphan*/  n_active; } ;
struct address_space {int dummy; } ;
typedef  int /*<<< orphan*/  fscache_rw_complete_t ;

/* Variables and functions */
 unsigned long FSCACHE_OP_MYTHREAD ; 
 unsigned long FSCACHE_OP_UNUSE_COOKIE ; 
 unsigned long FSCACHE_OP_WAITING ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fscache_n_retrievals_nomem ; 
 int /*<<< orphan*/  fscache_operation_init (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fscache_release_retrieval_op ; 
 int /*<<< orphan*/  fscache_retrieval_work ; 
 int /*<<< orphan*/  fscache_set_op_name (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  fscache_stat (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 struct fscache_retrieval* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct fscache_retrieval *fscache_alloc_retrieval(
	struct fscache_cookie *cookie,
	struct address_space *mapping,
	fscache_rw_complete_t end_io_func,
	void *context)
{
	struct fscache_retrieval *op;

	/* allocate a retrieval operation and attempt to submit it */
	op = kzalloc(sizeof(*op), GFP_NOIO);
	if (!op) {
		fscache_stat(&fscache_n_retrievals_nomem);
		return NULL;
	}

	fscache_operation_init(&op->op, fscache_release_retrieval_op);
	atomic_inc(&cookie->n_active);
	op->op.flags	= FSCACHE_OP_MYTHREAD |
		(1UL << FSCACHE_OP_WAITING) |
		(1UL << FSCACHE_OP_UNUSE_COOKIE);
	op->mapping	= mapping;
	op->end_io_func	= end_io_func;
	op->context	= context;
	op->start_time	= jiffies;
	INIT_WORK(&op->op.fast_work, fscache_retrieval_work);
	INIT_LIST_HEAD(&op->to_do);
	fscache_set_op_name(&op->op, "Retr");
	return op;
}