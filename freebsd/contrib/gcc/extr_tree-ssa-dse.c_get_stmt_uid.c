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
typedef  int /*<<< orphan*/  tree ;
struct TYPE_2__ {int uid; } ;

/* Variables and functions */
 scalar_t__ PHI_NODE ; 
 int /*<<< orphan*/  PHI_RESULT (int /*<<< orphan*/ ) ; 
 int SSA_NAME_VERSION (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int max_stmt_uid ; 
 TYPE_1__* stmt_ann (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned
get_stmt_uid (tree stmt)
{
  if (TREE_CODE (stmt) == PHI_NODE)
    return SSA_NAME_VERSION (PHI_RESULT (stmt)) + max_stmt_uid;

  return stmt_ann (stmt)->uid;
}