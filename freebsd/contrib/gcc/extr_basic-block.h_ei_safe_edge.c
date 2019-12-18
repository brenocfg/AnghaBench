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

__attribute__((used)) static inline edge
ei_safe_edge (edge_iterator i)
{
  return !ei_end_p (i) ? ei_edge (i) : NULL;
}