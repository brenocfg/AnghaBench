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
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
struct TYPE_3__ {int intoffset; int words; } ;
typedef  int HOST_WIDE_INT ;
typedef  TYPE_1__ CUMULATIVE_ARGS ;

/* Variables and functions */
 int BITS_PER_WORD ; 
 int BLKmode ; 
 int /*<<< orphan*/  MODE_INT ; 
 int mode_for_size (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
rs6000_darwin64_record_arg_advance_flush (CUMULATIVE_ARGS *cum,
					  HOST_WIDE_INT bitpos)
{
  unsigned int startbit, endbit;
  int intregs, intoffset;
  enum machine_mode mode;

  if (cum->intoffset == -1)
    return;

  intoffset = cum->intoffset;
  cum->intoffset = -1;

  if (intoffset % BITS_PER_WORD != 0)
    {
      mode = mode_for_size (BITS_PER_WORD - intoffset % BITS_PER_WORD,
			    MODE_INT, 0);
      if (mode == BLKmode)
	{
	  /* We couldn't find an appropriate mode, which happens,
	     e.g., in packed structs when there are 3 bytes to load.
	     Back intoffset back to the beginning of the word in this
	     case.  */
	  intoffset = intoffset & -BITS_PER_WORD;
	}
    }

  startbit = intoffset & -BITS_PER_WORD;
  endbit = (bitpos + BITS_PER_WORD - 1) & -BITS_PER_WORD;
  intregs = (endbit - startbit) / BITS_PER_WORD;
  cum->words += intregs;
}