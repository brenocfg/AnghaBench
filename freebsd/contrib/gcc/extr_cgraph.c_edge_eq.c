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
struct cgraph_edge {void const* call_stmt; } ;

/* Variables and functions */

__attribute__((used)) static int
edge_eq (const void *x, const void *y)
{
  return ((struct cgraph_edge *) x)->call_stmt == y;
}