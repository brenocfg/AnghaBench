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

/* Variables and functions */
 unsigned int BIGGEST_ALIGNMENT ; 
 unsigned int BITS_PER_UNIT ; 
 scalar_t__ CONSTANT_POOL_ADDRESS_P (int /*<<< orphan*/ ) ; 
 scalar_t__ CONST_VECTOR ; 
 int /*<<< orphan*/  CONST_VECTOR_ELT (int /*<<< orphan*/ ,int) ; 
 int CONST_VECTOR_NUNITS (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int GET_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ LABEL_REF ; 
 scalar_t__ NEED_GOT_RELOC ; 
 scalar_t__ SYMBOL_REF ; 
 scalar_t__ SYMBOL_REF_LOCAL_P (int /*<<< orphan*/ ) ; 
 unsigned int UNITS_PER_WORD ; 
#define  V2SImode 130 
#define  V4HImode 129 
#define  V8QImode 128 
 scalar_t__ arm_vector_mode_supported_p (int) ; 
 int /*<<< orphan*/  asm_out_file ; 
 int /*<<< orphan*/  assemble_integer (int /*<<< orphan*/ ,unsigned int,unsigned int,int) ; 
 int default_assemble_integer (int /*<<< orphan*/ ,unsigned int,int) ; 
 scalar_t__ flag_pic ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 scalar_t__ making_const_table ; 
 int /*<<< orphan*/  output_addr_const (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
arm_assemble_integer (rtx x, unsigned int size, int aligned_p)
{
  if (size == UNITS_PER_WORD && aligned_p)
    {
      fputs ("\t.word\t", asm_out_file);
      output_addr_const (asm_out_file, x);

      /* Mark symbols as position independent.  We only do this in the
	 .text segment, not in the .data segment.  */
      if (NEED_GOT_RELOC && flag_pic && making_const_table &&
	  (GET_CODE (x) == SYMBOL_REF || GET_CODE (x) == LABEL_REF))
	{
	  if (GET_CODE (x) == SYMBOL_REF
	      && (CONSTANT_POOL_ADDRESS_P (x)
		  || SYMBOL_REF_LOCAL_P (x)))
	    fputs ("(GOTOFF)", asm_out_file);
	  else if (GET_CODE (x) == LABEL_REF)
	    fputs ("(GOTOFF)", asm_out_file);
	  else
	    fputs ("(GOT)", asm_out_file);
	}
      fputc ('\n', asm_out_file);
      return true;
    }

  if (arm_vector_mode_supported_p (GET_MODE (x)))
    {
      int i, units;

      gcc_assert (GET_CODE (x) == CONST_VECTOR);

      units = CONST_VECTOR_NUNITS (x);

      switch (GET_MODE (x))
	{
	case V2SImode: size = 4; break;
	case V4HImode: size = 2; break;
	case V8QImode: size = 1; break;
	default:
	  gcc_unreachable ();
	}

      for (i = 0; i < units; i++)
	{
	  rtx elt;

	  elt = CONST_VECTOR_ELT (x, i);
	  assemble_integer
	    (elt, size, i == 0 ? BIGGEST_ALIGNMENT : size * BITS_PER_UNIT, 1);
	}

      return true;
    }

  return default_assemble_integer (x, size, aligned_p);
}