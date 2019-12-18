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
typedef  int /*<<< orphan*/  CGEN_INSN_INT ;
typedef  int /*<<< orphan*/  CGEN_INSN ;
typedef  int /*<<< orphan*/  CGEN_FIELDS ;
typedef  int /*<<< orphan*/  CGEN_CPU_DESC ;

/* Variables and functions */
 int /*<<< orphan*/  cgen_get_insn_operands (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/ * cgen_lookup_insn (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,unsigned char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

const CGEN_INSN *
cgen_lookup_get_insn_operands (CGEN_CPU_DESC cd,
			       const CGEN_INSN *insn,
			       CGEN_INSN_INT insn_int_value,
			       /* ??? CGEN_INSN_BYTES would be a nice type name to use here.  */
			       unsigned char *insn_bytes_value,
			       int length,
			       int *indices,
			       CGEN_FIELDS *fields)
{
  /* Pass non-zero for ALIAS_P only if INSN != NULL.
     If INSN == NULL, we want a real insn.  */
  insn = cgen_lookup_insn (cd, insn, insn_int_value, insn_bytes_value,
			   length, fields, insn != NULL);
  if (! insn)
    return NULL;

  cgen_get_insn_operands (cd, insn, fields, indices);
  return insn;
}