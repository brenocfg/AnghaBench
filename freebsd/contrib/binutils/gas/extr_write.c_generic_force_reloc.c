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
struct TYPE_3__ {scalar_t__ fx_r_type; int /*<<< orphan*/ * fx_subsy; int /*<<< orphan*/ * fx_addsy; } ;
typedef  TYPE_1__ fixS ;

/* Variables and functions */
 scalar_t__ BFD_RELOC_VTABLE_ENTRY ; 
 scalar_t__ BFD_RELOC_VTABLE_INHERIT ; 
 int S_FORCE_RELOC (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
generic_force_reloc (fixS *fix)
{
  if (fix->fx_r_type == BFD_RELOC_VTABLE_INHERIT
      || fix->fx_r_type == BFD_RELOC_VTABLE_ENTRY)
    return 1;

  if (fix->fx_addsy == NULL)
    return 0;

  return S_FORCE_RELOC (fix->fx_addsy, fix->fx_subsy == NULL);
}