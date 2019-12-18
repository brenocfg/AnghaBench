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
struct cgraph_edge {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cgraph_edge_remove_callee (struct cgraph_edge*) ; 
 int /*<<< orphan*/  cgraph_edge_remove_caller (struct cgraph_edge*) ; 

void
cgraph_remove_edge (struct cgraph_edge *e)
{
  /* Remove from callers list of the callee.  */
  cgraph_edge_remove_callee (e);

  /* Remove from callees list of the callers.  */
  cgraph_edge_remove_caller (e);
}