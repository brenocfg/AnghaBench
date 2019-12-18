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
typedef  int /*<<< orphan*/  u_int ;
struct TYPE_8__ {int nodekind; } ;
typedef  TYPE_1__ SmiNode ;

/* Variables and functions */
#define  SMI_NODEKIND_COMPLIANCE 133 
#define  SMI_NODEKIND_GROUP 132 
#define  SMI_NODEKIND_NODE 131 
#define  SMI_NODEKIND_NOTIFICATION 130 
#define  SMI_NODEKIND_SCALAR 129 
#define  SMI_NODEKIND_TABLE 128 
 int /*<<< orphan*/  errx (int,char*,int) ; 
 int /*<<< orphan*/  print_node (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_notification (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_scalar (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_table (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  save_node (TYPE_1__*) ; 

__attribute__((used)) static void
print_it(SmiNode *n, u_int level)
{
	switch (n->nodekind) {

	  case SMI_NODEKIND_NODE:
		print_node(n, level);
		break;

	  case SMI_NODEKIND_SCALAR:
		print_scalar(n, level);
		break;

	  case SMI_NODEKIND_TABLE:
		print_table(n, level);
		break;

	  case SMI_NODEKIND_COMPLIANCE:
	  case SMI_NODEKIND_GROUP:
		save_node(n);
		break;

	  case SMI_NODEKIND_NOTIFICATION:
		print_notification(n, level);
		break;

	  default:
		errx(1, "cannot handle %u nodes", n->nodekind);
	}
}