#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
struct TYPE_6__ {scalar_t__ nodekind; int* oid; int /*<<< orphan*/  access; } ;
typedef  TYPE_1__ SmiNode ;

/* Variables and functions */
 scalar_t__ SMI_NODEKIND_COLUMN ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  pindent (size_t) ; 
 int /*<<< orphan*/  print_access (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_name (TYPE_1__*) ; 
 int /*<<< orphan*/  print_type (TYPE_1__*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  save_node (TYPE_1__*) ; 

__attribute__((used)) static void
print_col(SmiNode *n, u_int level)
{
	assert (n->nodekind == SMI_NODEKIND_COLUMN);

	save_node(n);

	pindent(level);
	printf("(%u ", n->oid[level]);
	print_name(n);
	printf(" ");
	print_type(n);
	print_access(n->access);
	printf(")\n");
}