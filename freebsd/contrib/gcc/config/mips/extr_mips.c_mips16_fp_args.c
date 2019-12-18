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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int FP_ARG_FIRST ; 
 int GP_ARG_FIRST ; 
 scalar_t__ TARGET_64BIT ; 
 scalar_t__ TARGET_BIG_ENDIAN ; 
 int /*<<< orphan*/  TARGET_OLDABI ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char const*,char*,char*,...) ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 char** reg_names ; 

__attribute__((used)) static void
mips16_fp_args (FILE *file, int fp_code, int from_fp_p)
{
  const char *s;
  int gparg, fparg;
  unsigned int f;

  /* This code only works for the original 32 bit ABI and the O64 ABI.  */
  gcc_assert (TARGET_OLDABI);

  if (from_fp_p)
    s = "mfc1";
  else
    s = "mtc1";
  gparg = GP_ARG_FIRST;
  fparg = FP_ARG_FIRST;
  for (f = (unsigned int) fp_code; f != 0; f >>= 2)
    {
      if ((f & 3) == 1)
	{
	  if ((fparg & 1) != 0)
	    ++fparg;
	  fprintf (file, "\t%s\t%s,%s\n", s,
		   reg_names[gparg], reg_names[fparg]);
	}
      else if ((f & 3) == 2)
	{
	  if (TARGET_64BIT)
	    fprintf (file, "\td%s\t%s,%s\n", s,
		     reg_names[gparg], reg_names[fparg]);
	  else
	    {
	      if ((fparg & 1) != 0)
		++fparg;
	      if (TARGET_BIG_ENDIAN)
		fprintf (file, "\t%s\t%s,%s\n\t%s\t%s,%s\n", s,
			 reg_names[gparg], reg_names[fparg + 1], s,
			 reg_names[gparg + 1], reg_names[fparg]);
	      else
		fprintf (file, "\t%s\t%s,%s\n\t%s\t%s,%s\n", s,
			 reg_names[gparg], reg_names[fparg], s,
			 reg_names[gparg + 1], reg_names[fparg + 1]);
	      ++gparg;
	      ++fparg;
	    }
	}
      else
	gcc_unreachable ();

      ++gparg;
      ++fparg;
    }
}