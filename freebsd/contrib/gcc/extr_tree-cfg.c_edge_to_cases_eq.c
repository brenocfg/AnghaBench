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
struct edge_to_cases_elt {scalar_t__ e; } ;
typedef  scalar_t__ edge ;

/* Variables and functions */

__attribute__((used)) static int
edge_to_cases_eq (const void *p1, const void *p2)
{
  edge e1 = ((struct edge_to_cases_elt *)p1)->e;
  edge e2 = ((struct edge_to_cases_elt *)p2)->e;

  return e1 == e2;
}