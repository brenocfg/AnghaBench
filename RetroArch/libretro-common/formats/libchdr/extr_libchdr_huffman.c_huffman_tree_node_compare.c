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
struct node_t {scalar_t__ weight; scalar_t__ bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int huffman_tree_node_compare(const void *item1, const void *item2)
{
	const struct node_t *node1 = *(const struct node_t **)item1;
	const struct node_t *node2 = *(const struct node_t **)item2;
	if (node2->weight != node1->weight)
		return node2->weight - node1->weight;
	if (node2->bits - node1->bits == 0)
		fprintf(stderr, "identical node sort keys, should not happen!\n");
	return (int)node1->bits - (int)node2->bits;
}