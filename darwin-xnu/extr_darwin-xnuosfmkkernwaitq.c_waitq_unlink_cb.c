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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_2__ {int /*<<< orphan*/  right_setid; int /*<<< orphan*/  left_setid; } ;
struct waitq_link {TYPE_1__ wql_link; } ;
struct waitq {int dummy; } ;

/* Variables and functions */
 scalar_t__ WQL_LINK ; 
 int WQ_ITERATE_CONTINUE ; 
 int WQ_ITERATE_INVALID ; 
 int waitq_maybe_remove_link (struct waitq*,int /*<<< orphan*/ ,struct waitq_link*,struct waitq_link*,struct waitq_link*) ; 
 struct waitq_link* wql_get_link (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wql_is_valid (struct waitq_link*) ; 
 int /*<<< orphan*/  wql_put_link (struct waitq_link*) ; 
 scalar_t__ wql_type (struct waitq_link*) ; 

__attribute__((used)) static int waitq_unlink_cb(struct waitq *waitq, void *ctx,
			   struct waitq_link *link)
{
	uint64_t setid = *((uint64_t *)ctx);
	struct waitq_link *right, *left;
	int ret = 0;

	if (wql_type(link) != WQL_LINK)
		return WQ_ITERATE_CONTINUE;

	do  {
		left  = wql_get_link(link->wql_link.left_setid);
		right = wql_get_link(link->wql_link.right_setid);

		ret = waitq_maybe_remove_link(waitq, setid, link, left, right);

		wql_put_link(left);
		wql_put_link(right);

		if (!wql_is_valid(link))
			return WQ_ITERATE_INVALID;
		/* A ret value of UNLINKED will break us out of table walk */
	} while (ret == WQ_ITERATE_INVALID);

	return ret;
}