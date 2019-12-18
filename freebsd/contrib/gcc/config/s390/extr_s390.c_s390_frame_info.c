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
struct TYPE_2__ {int frame_size; int backchain_offset; int f0_offset; int f4_offset; int f8_offset; int high_fprs; int gprs_offset; int first_save_gpr_slot; } ;

/* Variables and functions */
 int BITS_PER_UNIT ; 
 int MIN (int,int) ; 
 int STACK_BOUNDARY ; 
 int STACK_POINTER_OFFSET ; 
 int STACK_POINTER_REGNUM ; 
 scalar_t__ TARGET_64BIT ; 
 scalar_t__ TARGET_BACKCHAIN ; 
 int /*<<< orphan*/  TARGET_PACKED_STACK ; 
 int /*<<< orphan*/  TARGET_TPF_PROFILING ; 
 int UNITS_PER_WORD ; 
 int cfun_fpr_bit_p (int) ; 
 TYPE_1__ cfun_frame_layout ; 
 int cfun_gprs_save_area_size ; 
 int /*<<< orphan*/  cfun_save_high_fprs_p ; 
 int /*<<< orphan*/  current_function_calls_alloca ; 
 scalar_t__ current_function_is_leaf ; 
 scalar_t__ current_function_outgoing_args_size ; 
 int /*<<< orphan*/  current_function_stdarg ; 
 int /*<<< orphan*/  fatal_error (char*) ; 
 int get_frame_size () ; 

__attribute__((used)) static void
s390_frame_info (void)
{
  int i;

  cfun_frame_layout.frame_size = get_frame_size ();
  if (!TARGET_64BIT && cfun_frame_layout.frame_size > 0x7fff0000)
    fatal_error ("total size of local variables exceeds architecture limit");
  
  if (!TARGET_PACKED_STACK)
    {
      cfun_frame_layout.backchain_offset = 0;
      cfun_frame_layout.f0_offset = 16 * UNITS_PER_WORD;
      cfun_frame_layout.f4_offset = cfun_frame_layout.f0_offset + 2 * 8;
      cfun_frame_layout.f8_offset = -cfun_frame_layout.high_fprs * 8;
      cfun_frame_layout.gprs_offset = (cfun_frame_layout.first_save_gpr_slot
				       * UNITS_PER_WORD);
    }
  else if (TARGET_BACKCHAIN) /* kernel stack layout */
    {
      cfun_frame_layout.backchain_offset = (STACK_POINTER_OFFSET
					    - UNITS_PER_WORD);
      cfun_frame_layout.gprs_offset 
	= (cfun_frame_layout.backchain_offset 
	   - (STACK_POINTER_REGNUM - cfun_frame_layout.first_save_gpr_slot + 1)
	   * UNITS_PER_WORD);
	  
      if (TARGET_64BIT)
	{
	  cfun_frame_layout.f4_offset 
	    = (cfun_frame_layout.gprs_offset
	       - 8 * (cfun_fpr_bit_p (2) + cfun_fpr_bit_p (3)));
	  
	  cfun_frame_layout.f0_offset 
	    = (cfun_frame_layout.f4_offset 
	       - 8 * (cfun_fpr_bit_p (0) + cfun_fpr_bit_p (1)));
	}
      else
	{
	  /* On 31 bit we have to care about alignment of the
	     floating point regs to provide fastest access.  */
	  cfun_frame_layout.f0_offset 
	    = ((cfun_frame_layout.gprs_offset 
		& ~(STACK_BOUNDARY / BITS_PER_UNIT - 1))
	       - 8 * (cfun_fpr_bit_p (0) + cfun_fpr_bit_p (1)));
	  
	  cfun_frame_layout.f4_offset 
	    = (cfun_frame_layout.f0_offset
	       - 8 * (cfun_fpr_bit_p (2) + cfun_fpr_bit_p (3)));
	}
    }
  else /* no backchain */
    {
      cfun_frame_layout.f4_offset 
	= (STACK_POINTER_OFFSET
	   - 8 * (cfun_fpr_bit_p (2) + cfun_fpr_bit_p (3)));
      
      cfun_frame_layout.f0_offset 
	= (cfun_frame_layout.f4_offset
	   - 8 * (cfun_fpr_bit_p (0) + cfun_fpr_bit_p (1)));
      
      cfun_frame_layout.gprs_offset 
	= cfun_frame_layout.f0_offset - cfun_gprs_save_area_size;
    }

  if (current_function_is_leaf
      && !TARGET_TPF_PROFILING
      && cfun_frame_layout.frame_size == 0
      && !cfun_save_high_fprs_p
      && !current_function_calls_alloca
      && !current_function_stdarg)
    return;

  if (!TARGET_PACKED_STACK)
    cfun_frame_layout.frame_size += (STACK_POINTER_OFFSET
				     + current_function_outgoing_args_size
				     + cfun_frame_layout.high_fprs * 8);
  else
    {
      if (TARGET_BACKCHAIN)
	cfun_frame_layout.frame_size += UNITS_PER_WORD;

      /* No alignment trouble here because f8-f15 are only saved under 
	 64 bit.  */
      cfun_frame_layout.f8_offset = (MIN (MIN (cfun_frame_layout.f0_offset,
					       cfun_frame_layout.f4_offset),
					  cfun_frame_layout.gprs_offset)
				     - cfun_frame_layout.high_fprs * 8);

      cfun_frame_layout.frame_size += cfun_frame_layout.high_fprs * 8;

      for (i = 0; i < 8; i++)
	if (cfun_fpr_bit_p (i))
	  cfun_frame_layout.frame_size += 8;
      
      cfun_frame_layout.frame_size += cfun_gprs_save_area_size;
      
      /* If under 31 bit an odd number of gprs has to be saved we have to adjust
	 the frame size to sustain 8 byte alignment of stack frames.  */
      cfun_frame_layout.frame_size = ((cfun_frame_layout.frame_size +
				       STACK_BOUNDARY / BITS_PER_UNIT - 1)
				      & ~(STACK_BOUNDARY / BITS_PER_UNIT - 1));

      cfun_frame_layout.frame_size += current_function_outgoing_args_size;
    }
}