#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  nodes; int /*<<< orphan*/  preferred_node; } ;
struct TYPE_3__ {int /*<<< orphan*/  user_nodemask; } ;
struct mempolicy {unsigned short flags; unsigned short mode; TYPE_2__ v; TYPE_1__ w; } ;
typedef  int /*<<< orphan*/  nodemask_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int ENOSPC ; 
#define  MPOL_BIND 131 
#define  MPOL_DEFAULT 130 
 unsigned short MPOL_F_LOCAL ; 
 unsigned short MPOL_F_RELATIVE_NODES ; 
 unsigned short MPOL_F_STATIC_NODES ; 
#define  MPOL_INTERLEAVE 129 
 unsigned short MPOL_LOCAL ; 
 unsigned short MPOL_MODE_FLAGS ; 
#define  MPOL_PREFERRED 128 
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 struct mempolicy default_policy ; 
 int /*<<< orphan*/  node_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nodelist_scnprintf (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nodes_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nodes_empty (int /*<<< orphan*/ ) ; 
 char** policy_types ; 
 int /*<<< orphan*/  snprintf (char*,int,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 

int mpol_to_str(char *buffer, int maxlen, struct mempolicy *pol, int no_context)
{
	char *p = buffer;
	int l;
	nodemask_t nodes;
	unsigned short mode;
	unsigned short flags = pol ? pol->flags : 0;

	/*
	 * Sanity check:  room for longest mode, flag and some nodes
	 */
	VM_BUG_ON(maxlen < strlen("interleave") + strlen("relative") + 16);

	if (!pol || pol == &default_policy)
		mode = MPOL_DEFAULT;
	else
		mode = pol->mode;

	switch (mode) {
	case MPOL_DEFAULT:
		nodes_clear(nodes);
		break;

	case MPOL_PREFERRED:
		nodes_clear(nodes);
		if (flags & MPOL_F_LOCAL)
			mode = MPOL_LOCAL;	/* pseudo-policy */
		else
			node_set(pol->v.preferred_node, nodes);
		break;

	case MPOL_BIND:
		/* Fall through */
	case MPOL_INTERLEAVE:
		if (no_context)
			nodes = pol->w.user_nodemask;
		else
			nodes = pol->v.nodes;
		break;

	default:
		BUG();
	}

	l = strlen(policy_types[mode]);
	if (buffer + maxlen < p + l + 1)
		return -ENOSPC;

	strcpy(p, policy_types[mode]);
	p += l;

	if (flags & MPOL_MODE_FLAGS) {
		if (buffer + maxlen < p + 2)
			return -ENOSPC;
		*p++ = '=';

		/*
		 * Currently, the only defined flags are mutually exclusive
		 */
		if (flags & MPOL_F_STATIC_NODES)
			p += snprintf(p, buffer + maxlen - p, "static");
		else if (flags & MPOL_F_RELATIVE_NODES)
			p += snprintf(p, buffer + maxlen - p, "relative");
	}

	if (!nodes_empty(nodes)) {
		if (buffer + maxlen < p + 2)
			return -ENOSPC;
		*p++ = ':';
	 	p += nodelist_scnprintf(p, buffer + maxlen - p, nodes);
	}
	return p - buffer;
}