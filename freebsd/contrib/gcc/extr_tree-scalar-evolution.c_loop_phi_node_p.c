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
struct TYPE_2__ {scalar_t__ header; } ;

/* Variables and functions */
 scalar_t__ bb_for_stmt (int /*<<< orphan*/ ) ; 
 TYPE_1__* loop_containing_stmt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
loop_phi_node_p (tree phi)
{
  /* The implementation of this function is based on the following
     property: "all the loop-phi-nodes of a loop are contained in the
     loop's header basic block".  */

  return loop_containing_stmt (phi)->header == bb_for_stmt (phi);
}