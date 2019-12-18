#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ length; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISA_EXT_CORE1 ; 
 int /*<<< orphan*/  ISA_EXT_CORE2 ; 
 int /*<<< orphan*/  ISA_MAX ; 
 int /*<<< orphan*/  ISA_MEP ; 
 int /*<<< orphan*/  cgen_bitset_add (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgen_bitset_init (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgen_bitset_set (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__ mep_all_core_isas_mask ; 

void
init_mep_all_core_isas_mask (void)
{
  if (mep_all_core_isas_mask.length != 0)
    return;
  cgen_bitset_init (& mep_all_core_isas_mask, ISA_MAX);
  cgen_bitset_set (& mep_all_core_isas_mask, ISA_MEP);
  /* begin-all-core-isas */
  cgen_bitset_add (& mep_all_core_isas_mask, ISA_EXT_CORE1);
  cgen_bitset_add (& mep_all_core_isas_mask, ISA_EXT_CORE2);
  /* end-all-core-isas */
}