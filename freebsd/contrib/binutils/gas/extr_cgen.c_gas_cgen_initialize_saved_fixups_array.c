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
struct TYPE_2__ {scalar_t__ num_fixups_in_chain; } ;

/* Variables and functions */
 int MAX_SAVED_FIXUP_CHAINS ; 
 TYPE_1__* stored_fixups ; 

void
gas_cgen_initialize_saved_fixups_array ()
{
  int i = 0;

  while (i < MAX_SAVED_FIXUP_CHAINS)
    stored_fixups[i++].num_fixups_in_chain = 0;
}