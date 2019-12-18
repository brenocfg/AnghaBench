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
struct constant_pool {int /*<<< orphan*/  pool_insn; struct constant* execute; int /*<<< orphan*/  label; struct constant** constants; } ;
struct constant {int /*<<< orphan*/  value; int /*<<< orphan*/  label; struct constant* next; } ;
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 scalar_t__ CONST ; 
 int /*<<< orphan*/  GEN_INT (int) ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INSN_ADDRESSES_NEW (int /*<<< orphan*/ ,int) ; 
 int NR_C_MODES ; 
 int /*<<< orphan*/  Pmode ; 
 scalar_t__ TARGET_CPU_ZARCH ; 
 scalar_t__ UNSPEC ; 
 int /*<<< orphan*/  UNSPECV_POOL_ENTRY ; 
 scalar_t__ UNSPEC_LTREL_OFFSET ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ XINT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int XVECLEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * constant_modes ; 
 int /*<<< orphan*/  emit_barrier_after (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_insn_after (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_label_after (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_pool_align (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_pool_section_end () ; 
 int /*<<< orphan*/  gen_pool_section_start () ; 
 int /*<<< orphan*/  gen_rtvec (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_CONST (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_LABEL_REF (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_MINUS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_UNSPEC_VOLATILE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s390_execute_target (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
s390_dump_pool (struct constant_pool *pool, bool remote_label)
{
  struct constant *c;
  rtx insn = pool->pool_insn;
  int i;

  /* Switch to rodata section.  */
  if (TARGET_CPU_ZARCH)
    {
      insn = emit_insn_after (gen_pool_section_start (), insn);
      INSN_ADDRESSES_NEW (insn, -1);
    }

  /* Ensure minimum pool alignment.  */
  if (TARGET_CPU_ZARCH)
    insn = emit_insn_after (gen_pool_align (GEN_INT (8)), insn);
  else
    insn = emit_insn_after (gen_pool_align (GEN_INT (4)), insn);
  INSN_ADDRESSES_NEW (insn, -1);

  /* Emit pool base label.  */
  if (!remote_label)
    {
      insn = emit_label_after (pool->label, insn);
      INSN_ADDRESSES_NEW (insn, -1);
    }

  /* Dump constants in descending alignment requirement order,
     ensuring proper alignment for every constant.  */
  for (i = 0; i < NR_C_MODES; i++)
    for (c = pool->constants[i]; c; c = c->next)
      {
	/* Convert UNSPEC_LTREL_OFFSET unspecs to pool-relative references.  */
	rtx value = c->value;
	if (GET_CODE (value) == CONST
	    && GET_CODE (XEXP (value, 0)) == UNSPEC
	    && XINT (XEXP (value, 0), 1) == UNSPEC_LTREL_OFFSET
	    && XVECLEN (XEXP (value, 0), 0) == 1)
	  {
	    value = gen_rtx_MINUS (Pmode, XVECEXP (XEXP (value, 0), 0, 0),
				   gen_rtx_LABEL_REF (VOIDmode, pool->label));
	    value = gen_rtx_CONST (VOIDmode, value);
	  }

	insn = emit_label_after (c->label, insn);
	INSN_ADDRESSES_NEW (insn, -1);

	value = gen_rtx_UNSPEC_VOLATILE (constant_modes[i],
					 gen_rtvec (1, value),
					 UNSPECV_POOL_ENTRY);
	insn = emit_insn_after (value, insn);
	INSN_ADDRESSES_NEW (insn, -1);
      }

  /* Ensure minimum alignment for instructions.  */
  insn = emit_insn_after (gen_pool_align (GEN_INT (2)), insn);
  INSN_ADDRESSES_NEW (insn, -1);

  /* Output in-pool execute template insns.  */
  for (c = pool->execute; c; c = c->next)
    {
      insn = emit_label_after (c->label, insn);
      INSN_ADDRESSES_NEW (insn, -1);

      insn = emit_insn_after (s390_execute_target (c->value), insn);
      INSN_ADDRESSES_NEW (insn, -1);
    }

  /* Switch back to previous section.  */
  if (TARGET_CPU_ZARCH)
    {
      insn = emit_insn_after (gen_pool_section_end (), insn);
      INSN_ADDRESSES_NEW (insn, -1);
    }

  insn = emit_barrier_after (insn);
  INSN_ADDRESSES_NEW (insn, -1);

  /* Remove placeholder insn.  */
  remove_insn (pool->pool_insn);
}