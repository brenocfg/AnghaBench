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
struct TYPE_2__ {int finalized; } ;

/* Variables and functions */
 TYPE_1__* cgraph_varpool_node (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
var_finalized_p (tree var)
{
  return cgraph_varpool_node (var)->finalized;
}