#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
struct TYPE_8__ {scalar_t__ nodekind; int* oid; char* name; int /*<<< orphan*/  access; } ;
typedef  TYPE_1__ SmiNode ;

/* Variables and functions */
 scalar_t__ SMI_NODEKIND_SCALAR ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  pindent (size_t) ; 
 int /*<<< orphan*/  print_access (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_name (TYPE_1__*) ; 
 int /*<<< orphan*/  print_type (TYPE_1__*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  save_node (TYPE_1__*) ; 
 TYPE_1__* smiGetParentNode (TYPE_1__*) ; 

__attribute__((used)) static void
print_scalar(SmiNode *n, u_int level)
{
	SmiNode *p;

	assert (n->nodekind == SMI_NODEKIND_SCALAR);

	save_node(n);

	pindent(level);
	printf("(%u ", n->oid[level]);
	print_name(n);
	printf(" ");
	print_type(n);

	/* generate the operation from the parent node name */
	p = smiGetParentNode(n);
	printf(" op_%s", p->name);

	print_access(n->access);

	printf(")\n");
}