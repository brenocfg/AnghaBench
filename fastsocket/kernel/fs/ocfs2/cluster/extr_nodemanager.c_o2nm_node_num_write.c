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
struct o2nm_node {unsigned long nd_num; int /*<<< orphan*/  nd_set_attributes; } ;
struct o2nm_cluster {int /*<<< orphan*/  cl_nodes_lock; int /*<<< orphan*/  cl_nodes_bitmap; struct o2nm_node** cl_nodes; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EEXIST ; 
 size_t EINVAL ; 
 size_t ERANGE ; 
 unsigned long O2NM_MAX_NODES ; 
 int /*<<< orphan*/  O2NM_NODE_ATTR_ADDRESS ; 
 int /*<<< orphan*/  O2NM_NODE_ATTR_PORT ; 
 int /*<<< orphan*/  set_bit (unsigned long,int /*<<< orphan*/ ) ; 
 unsigned long simple_strtoul (char*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct o2nm_cluster* to_o2nm_cluster_from_node (struct o2nm_node*) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t o2nm_node_num_write(struct o2nm_node *node, const char *page,
				   size_t count)
{
	struct o2nm_cluster *cluster = to_o2nm_cluster_from_node(node);
	unsigned long tmp;
	char *p = (char *)page;

	tmp = simple_strtoul(p, &p, 0);
	if (!p || (*p && (*p != '\n')))
		return -EINVAL;

	if (tmp >= O2NM_MAX_NODES)
		return -ERANGE;

	/* once we're in the cl_nodes tree networking can look us up by
	 * node number and try to use our address and port attributes
	 * to connect to this node.. make sure that they've been set
	 * before writing the node attribute? */
	if (!test_bit(O2NM_NODE_ATTR_ADDRESS, &node->nd_set_attributes) ||
	    !test_bit(O2NM_NODE_ATTR_PORT, &node->nd_set_attributes))
		return -EINVAL; /* XXX */

	write_lock(&cluster->cl_nodes_lock);
	if (cluster->cl_nodes[tmp])
		p = NULL;
	else  {
		cluster->cl_nodes[tmp] = node;
		node->nd_num = tmp;
		set_bit(tmp, cluster->cl_nodes_bitmap);
	}
	write_unlock(&cluster->cl_nodes_lock);
	if (p == NULL)
		return -EEXIST;

	return count;
}