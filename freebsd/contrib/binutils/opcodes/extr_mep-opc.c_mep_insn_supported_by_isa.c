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
typedef  int /*<<< orphan*/  CGEN_INSN ;
typedef  int /*<<< orphan*/  CGEN_BITSET ;
typedef  int /*<<< orphan*/  CGEN_ATTR_VALUE_BITSET_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  CGEN_INSN_BITSET_ATTR_VALUE (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CGEN_INSN_ISA ; 
 int cgen_bitset_intersect_p (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
mep_insn_supported_by_isa (const CGEN_INSN *insn, CGEN_ATTR_VALUE_BITSET_TYPE *isa_mask)
{
  CGEN_BITSET insn_isas = CGEN_INSN_BITSET_ATTR_VALUE (insn, CGEN_INSN_ISA);
  return cgen_bitset_intersect_p (& insn_isas, isa_mask);
}