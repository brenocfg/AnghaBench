#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* edge ;
struct TYPE_3__ {scalar_t__ aux; } ;

/* Variables and functions */
 int /*<<< orphan*/  edge_aux_obstack ; 
 scalar_t__ first_edge_aux_obj ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ obstack_alloc (int /*<<< orphan*/ *,int) ; 

inline void
alloc_aux_for_edge (edge e, int size)
{
  /* Verify that aux field is clear.  */
  gcc_assert (!e->aux && first_edge_aux_obj);
  e->aux = obstack_alloc (&edge_aux_obstack, size);
  memset (e->aux, 0, size);
}