#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* basic_block ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BB_DUPLICATED ; 
 int /*<<< orphan*/  add_phi_args_after_copy_bb (TYPE_1__*) ; 

void
add_phi_args_after_copy (basic_block *region_copy, unsigned n_region)
{
  unsigned i;

  for (i = 0; i < n_region; i++)
    region_copy[i]->flags |= BB_DUPLICATED;

  for (i = 0; i < n_region; i++)
    add_phi_args_after_copy_bb (region_copy[i]);

  for (i = 0; i < n_region; i++)
    region_copy[i]->flags &= ~BB_DUPLICATED;
}