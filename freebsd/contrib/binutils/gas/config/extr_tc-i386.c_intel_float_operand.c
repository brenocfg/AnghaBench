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

/* Variables and functions */

__attribute__((used)) static int
intel_float_operand (const char *mnemonic)
{
  /* Note that the value returned is meaningful only for opcodes with (memory)
     operands, hence the code here is free to improperly handle opcodes that
     have no operands (for better performance and smaller code). */

  if (mnemonic[0] != 'f')
    return 0; /* non-math */

  switch (mnemonic[1])
    {
    /* fclex, fdecstp, fdisi, femms, feni, fincstp, finit, fsetpm, and
       the fs segment override prefix not currently handled because no
       call path can make opcodes without operands get here */
    case 'i':
      return 2 /* integer op */;
    case 'l':
      if (mnemonic[2] == 'd' && (mnemonic[3] == 'c' || mnemonic[3] == 'e'))
	return 3; /* fldcw/fldenv */
      break;
    case 'n':
      if (mnemonic[2] != 'o' /* fnop */)
	return 3; /* non-waiting control op */
      break;
    case 'r':
      if (mnemonic[2] == 's')
	return 3; /* frstor/frstpm */
      break;
    case 's':
      if (mnemonic[2] == 'a')
	return 3; /* fsave */
      if (mnemonic[2] == 't')
	{
	  switch (mnemonic[3])
	    {
	    case 'c': /* fstcw */
	    case 'd': /* fstdw */
	    case 'e': /* fstenv */
	    case 's': /* fsts[gw] */
	      return 3;
	    }
	}
      break;
    case 'x':
      if (mnemonic[2] == 'r' || mnemonic[2] == 's')
	return 0; /* fxsave/fxrstor are not really math ops */
      break;
    }

  return 1;
}