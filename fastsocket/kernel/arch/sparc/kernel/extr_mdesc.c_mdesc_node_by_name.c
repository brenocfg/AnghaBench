#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u64 ;
struct TYPE_5__ {int node_sz; } ;
struct mdesc_handle {TYPE_2__ mdesc; } ;
struct TYPE_4__ {size_t val; } ;
struct mdesc_elem {scalar_t__ tag; int name_offset; TYPE_1__ d; } ;

/* Variables and functions */
 size_t MDESC_NODE_NULL ; 
 scalar_t__ MD_NODE ; 
 char* name_block (TYPE_2__*) ; 
 struct mdesc_elem* node_block (TYPE_2__*) ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 

u64 mdesc_node_by_name(struct mdesc_handle *hp,
		       u64 from_node, const char *name)
{
	struct mdesc_elem *ep = node_block(&hp->mdesc);
	const char *names = name_block(&hp->mdesc);
	u64 last_node = hp->mdesc.node_sz / 16;
	u64 ret;

	if (from_node == MDESC_NODE_NULL) {
		ret = from_node = 0;
	} else if (from_node >= last_node) {
		return MDESC_NODE_NULL;
	} else {
		ret = ep[from_node].d.val;
	}

	while (ret < last_node) {
		if (ep[ret].tag != MD_NODE)
			return MDESC_NODE_NULL;
		if (!strcmp(names + ep[ret].name_offset, name))
			break;
		ret = ep[ret].d.val;
	}
	if (ret >= last_node)
		ret = MDESC_NODE_NULL;
	return ret;
}