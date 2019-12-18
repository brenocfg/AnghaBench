#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
struct TYPE_10__ {scalar_t__ nodekind; int* oid; } ;
typedef  TYPE_1__ SmiNode ;

/* Variables and functions */
 scalar_t__ SMI_NODEKIND_NODE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  pindent (size_t) ; 
 int /*<<< orphan*/  print_it (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  print_name (TYPE_1__*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  save_node (TYPE_1__*) ; 
 TYPE_1__* smiGetFirstChildNode (TYPE_1__*) ; 
 TYPE_1__* smiGetNextChildNode (TYPE_1__*) ; 

__attribute__((used)) static void
print_node(SmiNode *n, u_int level)
{
	assert (n->nodekind == SMI_NODEKIND_NODE);

	save_node(n);

	pindent(level);
	printf("(%u ", n->oid[level]);
	print_name(n);
	printf("\n");

	n = smiGetFirstChildNode(n);
	while (n != NULL) {
		print_it(n, level + 1);
		n = smiGetNextChildNode(n);
	}
	pindent(level);
	printf(")\n");
}