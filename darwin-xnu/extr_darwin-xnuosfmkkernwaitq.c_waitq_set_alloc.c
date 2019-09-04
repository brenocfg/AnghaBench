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
struct waitq_set {int dummy; } ;
typedef  scalar_t__ kern_return_t ;

/* Variables and functions */
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ waitq_set_init (struct waitq_set*,int,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  waitq_set_zone ; 
 scalar_t__ zalloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ,struct waitq_set*) ; 

struct waitq_set *waitq_set_alloc(int policy, void *prepost_hook)
{
	struct waitq_set *wqset;

	wqset = (struct waitq_set *)zalloc(waitq_set_zone);
	if (!wqset)
		panic("Can't allocate a new waitq set from zone %p", waitq_set_zone);

	kern_return_t ret;
	ret = waitq_set_init(wqset, policy, NULL, prepost_hook);
	if (ret != KERN_SUCCESS) {
		zfree(waitq_set_zone, wqset);
		wqset = NULL;
	}

	return wqset;
}