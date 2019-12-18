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
typedef  int /*<<< orphan*/  rtx ;
typedef  enum attr_unit { ____Placeholder_attr_unit } attr_unit ;
typedef  enum attr_type { ____Placeholder_attr_type } attr_type ;
typedef  enum attr_memory { ____Placeholder_attr_memory } attr_memory ;

/* Variables and functions */
 int /*<<< orphan*/  GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEM ; 
 int MEMORY_BOTH ; 
 int MEMORY_LOAD ; 
 int MEMORY_STORE ; 
 int /*<<< orphan*/  NULL_RTX ; 
#define  PROCESSOR_AMDFAM10 135 
#define  PROCESSOR_ATHLON 134 
#define  PROCESSOR_GENERIC32 133 
#define  PROCESSOR_GENERIC64 132 
#define  PROCESSOR_K6 131 
#define  PROCESSOR_K8 130 
#define  PROCESSOR_PENTIUM 129 
#define  PROCESSOR_PENTIUMPRO 128 
 scalar_t__ REG_NOTE_KIND (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_DEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_SRC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TARGET_ATHLON ; 
 int TYPE_FMOV ; 
 int TYPE_IMOV ; 
 int TYPE_POP ; 
 int TYPE_PUSH ; 
 int UNIT_INTEGER ; 
 int UNIT_UNKNOWN ; 
 int /*<<< orphan*/  get_attr_fp_int_src (int /*<<< orphan*/ ) ; 
 int get_attr_memory (int /*<<< orphan*/ ) ; 
 int get_attr_type (int /*<<< orphan*/ ) ; 
 int get_attr_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ix86_agi_dependent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ix86_flags_dependent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int ix86_tune ; 
 int recog_memoized (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtx_equal_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  single_set (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ix86_adjust_cost (rtx insn, rtx link, rtx dep_insn, int cost)
{
  enum attr_type insn_type, dep_insn_type;
  enum attr_memory memory;
  rtx set, set2;
  int dep_insn_code_number;

  /* Anti and output dependencies have zero cost on all CPUs.  */
  if (REG_NOTE_KIND (link) != 0)
    return 0;

  dep_insn_code_number = recog_memoized (dep_insn);

  /* If we can't recognize the insns, we can't really do anything.  */
  if (dep_insn_code_number < 0 || recog_memoized (insn) < 0)
    return cost;

  insn_type = get_attr_type (insn);
  dep_insn_type = get_attr_type (dep_insn);

  switch (ix86_tune)
    {
    case PROCESSOR_PENTIUM:
      /* Address Generation Interlock adds a cycle of latency.  */
      if (ix86_agi_dependent (insn, dep_insn, insn_type))
	cost += 1;

      /* ??? Compares pair with jump/setcc.  */
      if (ix86_flags_dependent (insn, dep_insn, insn_type))
	cost = 0;

      /* Floating point stores require value to be ready one cycle earlier.  */
      if (insn_type == TYPE_FMOV
	  && get_attr_memory (insn) == MEMORY_STORE
	  && !ix86_agi_dependent (insn, dep_insn, insn_type))
	cost += 1;
      break;

    case PROCESSOR_PENTIUMPRO:
      memory = get_attr_memory (insn);

      /* INT->FP conversion is expensive.  */
      if (get_attr_fp_int_src (dep_insn))
	cost += 5;

      /* There is one cycle extra latency between an FP op and a store.  */
      if (insn_type == TYPE_FMOV
	  && (set = single_set (dep_insn)) != NULL_RTX
	  && (set2 = single_set (insn)) != NULL_RTX
	  && rtx_equal_p (SET_DEST (set), SET_SRC (set2))
	  && GET_CODE (SET_DEST (set2)) == MEM)
	cost += 1;

      /* Show ability of reorder buffer to hide latency of load by executing
	 in parallel with previous instruction in case
	 previous instruction is not needed to compute the address.  */
      if ((memory == MEMORY_LOAD || memory == MEMORY_BOTH)
	  && !ix86_agi_dependent (insn, dep_insn, insn_type))
	{
	  /* Claim moves to take one cycle, as core can issue one load
	     at time and the next load can start cycle later.  */
	  if (dep_insn_type == TYPE_IMOV
	      || dep_insn_type == TYPE_FMOV)
	    cost = 1;
	  else if (cost > 1)
	    cost--;
	}
      break;

    case PROCESSOR_K6:
      memory = get_attr_memory (insn);

      /* The esp dependency is resolved before the instruction is really
         finished.  */
      if ((insn_type == TYPE_PUSH || insn_type == TYPE_POP)
	  && (dep_insn_type == TYPE_PUSH || dep_insn_type == TYPE_POP))
	return 1;

      /* INT->FP conversion is expensive.  */
      if (get_attr_fp_int_src (dep_insn))
	cost += 5;

      /* Show ability of reorder buffer to hide latency of load by executing
	 in parallel with previous instruction in case
	 previous instruction is not needed to compute the address.  */
      if ((memory == MEMORY_LOAD || memory == MEMORY_BOTH)
	  && !ix86_agi_dependent (insn, dep_insn, insn_type))
	{
	  /* Claim moves to take one cycle, as core can issue one load
	     at time and the next load can start cycle later.  */
	  if (dep_insn_type == TYPE_IMOV
	      || dep_insn_type == TYPE_FMOV)
	    cost = 1;
	  else if (cost > 2)
	    cost -= 2;
	  else
	    cost = 1;
	}
      break;

    case PROCESSOR_ATHLON:
    case PROCESSOR_K8:
    case PROCESSOR_AMDFAM10:
    case PROCESSOR_GENERIC32:
    case PROCESSOR_GENERIC64:
      memory = get_attr_memory (insn);

      /* Show ability of reorder buffer to hide latency of load by executing
	 in parallel with previous instruction in case
	 previous instruction is not needed to compute the address.  */
      if ((memory == MEMORY_LOAD || memory == MEMORY_BOTH)
	  && !ix86_agi_dependent (insn, dep_insn, insn_type))
	{
	  enum attr_unit unit = get_attr_unit (insn);
	  int loadcost = 3;

	  /* Because of the difference between the length of integer and
	     floating unit pipeline preparation stages, the memory operands
	     for floating point are cheaper.

	     ??? For Athlon it the difference is most probably 2.  */
	  if (unit == UNIT_INTEGER || unit == UNIT_UNKNOWN)
	    loadcost = 3;
	  else
	    loadcost = TARGET_ATHLON ? 2 : 0;

	  if (cost >= loadcost)
	    cost -= loadcost;
	  else
	    cost = 0;
	}

    default:
      break;
    }

  return cost;
}