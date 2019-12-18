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
typedef  int /*<<< orphan*/  edge_iterator ;
typedef  int /*<<< orphan*/ * edge ;

/* Variables and functions */
 int /*<<< orphan*/ * ei_edge (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ei_end_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool
ei_cond (edge_iterator ei, edge *p)
{
  if (!ei_end_p (ei))
    {
      *p = ei_edge (ei);
      return 1;
    }
  else
    {
      *p = NULL;
      return 0;
    }
}