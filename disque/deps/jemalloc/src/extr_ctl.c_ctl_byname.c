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
typedef  int /*<<< orphan*/  ctl_node_t ;
struct TYPE_3__ {int (* ctl ) (size_t*,size_t,void*,size_t*,void*,size_t) ;} ;
typedef  TYPE_1__ ctl_named_node_t ;

/* Variables and functions */
 int CTL_MAX_DEPTH ; 
 int EAGAIN ; 
 int ENOENT ; 
 scalar_t__ ctl_init () ; 
 int /*<<< orphan*/  ctl_initialized ; 
 int ctl_lookup (char const*,int /*<<< orphan*/  const**,size_t*,size_t*) ; 
 TYPE_1__* ctl_named_node (int /*<<< orphan*/  const*) ; 
 int stub1 (size_t*,size_t,void*,size_t*,void*,size_t) ; 

int
ctl_byname(const char *name, void *oldp, size_t *oldlenp, void *newp,
    size_t newlen)
{
	int ret;
	size_t depth;
	ctl_node_t const *nodes[CTL_MAX_DEPTH];
	size_t mib[CTL_MAX_DEPTH];
	const ctl_named_node_t *node;

	if (!ctl_initialized && ctl_init()) {
		ret = EAGAIN;
		goto label_return;
	}

	depth = CTL_MAX_DEPTH;
	ret = ctl_lookup(name, nodes, mib, &depth);
	if (ret != 0)
		goto label_return;

	node = ctl_named_node(nodes[depth-1]);
	if (node != NULL && node->ctl)
		ret = node->ctl(mib, depth, oldp, oldlenp, newp, newlen);
	else {
		/* The name refers to a partial path through the ctl tree. */
		ret = ENOENT;
	}

label_return:
	return(ret);
}