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
typedef  int /*<<< orphan*/  valueT ;
typedef  scalar_t__ LITTLENUM_TYPE ;

/* Variables and functions */
 scalar_t__ ARM_CPU_HAS_FEATURE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MAX_LITTLENUMS ; 
 char* _ (char*) ; 
 char* atof_ieee (char*,int,scalar_t__*) ; 
 int /*<<< orphan*/  cpu_variant ; 
 int /*<<< orphan*/  fpu_endian_pure ; 
 char* input_line_pointer ; 
 int /*<<< orphan*/  md_number_to_chars (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ target_big_endian ; 

char *
md_atof (int type, char * litP, int * sizeP)
{
  int prec;
  LITTLENUM_TYPE words[MAX_LITTLENUMS];
  char *t;
  int i;

  switch (type)
    {
    case 'f':
    case 'F':
    case 's':
    case 'S':
      prec = 2;
      break;

    case 'd':
    case 'D':
    case 'r':
    case 'R':
      prec = 4;
      break;

    case 'x':
    case 'X':
      prec = 6;
      break;

    case 'p':
    case 'P':
      prec = 6;
      break;

    default:
      *sizeP = 0;
      return _("bad call to MD_ATOF()");
    }

  t = atof_ieee (input_line_pointer, type, words);
  if (t)
    input_line_pointer = t;
  *sizeP = prec * 2;

  if (target_big_endian)
    {
      for (i = 0; i < prec; i++)
	{
	  md_number_to_chars (litP, (valueT) words[i], 2);
	  litP += 2;
	}
    }
  else
    {
      if (ARM_CPU_HAS_FEATURE (cpu_variant, fpu_endian_pure))
	for (i = prec - 1; i >= 0; i--)
	  {
	    md_number_to_chars (litP, (valueT) words[i], 2);
	    litP += 2;
	  }
      else
	/* For a 4 byte float the order of elements in `words' is 1 0.
	   For an 8 byte float the order is 1 0 3 2.  */
	for (i = 0; i < prec; i += 2)
	  {
	    md_number_to_chars (litP, (valueT) words[i + 1], 2);
	    md_number_to_chars (litP + 2, (valueT) words[i], 2);
	    litP += 4;
	  }
    }

  return 0;
}