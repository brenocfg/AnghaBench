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
typedef  scalar_t__ offsetT ;

/* Variables and functions */
 scalar_t__ ISALPHA (char) ; 
 int MAXIMUM_NUMBER_OF_CHARS_FOR_FLOAT ; 
 int /*<<< orphan*/  SKIP_WHITESPACE () ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  as_bad (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  demand_empty_rest_of_line () ; 
 scalar_t__ flag_mri ; 
 char* frag_more (int) ; 
 scalar_t__ get_absolute_expression () ; 
 int hex_float (int,char*) ; 
 int /*<<< orphan*/  ignore_rest_of_line () ; 
 char* input_line_pointer ; 
 int /*<<< orphan*/  know (int) ; 
 char* md_atof (int,char*,int*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,unsigned int) ; 
 int /*<<< orphan*/  mri_comment_end (char*,char) ; 
 char* mri_comment_field (char*) ; 

void
s_float_space (int float_type)
{
  offsetT count;
  int flen;
  char temp[MAXIMUM_NUMBER_OF_CHARS_FOR_FLOAT];
  char *stop = NULL;
  char stopc = 0;

  if (flag_mri)
    stop = mri_comment_field (&stopc);

  count = get_absolute_expression ();

  SKIP_WHITESPACE ();
  if (*input_line_pointer != ',')
    {
      as_bad (_("missing value"));
      ignore_rest_of_line ();
      if (flag_mri)
	mri_comment_end (stop, stopc);
      return;
    }

  ++input_line_pointer;

  SKIP_WHITESPACE ();

  /* Skip any 0{letter} that may be present.  Don't even check if the
   * letter is legal.  */
  if (input_line_pointer[0] == '0'
      && ISALPHA (input_line_pointer[1]))
    input_line_pointer += 2;

  /* Accept :xxxx, where the x's are hex digits, for a floating point
     with the exact digits specified.  */
  if (input_line_pointer[0] == ':')
    {
      flen = hex_float (float_type, temp);
      if (flen < 0)
	{
	  ignore_rest_of_line ();
	  if (flag_mri)
	    mri_comment_end (stop, stopc);
	  return;
	}
    }
  else
    {
      char *err;

      err = md_atof (float_type, temp, &flen);
      know (flen <= MAXIMUM_NUMBER_OF_CHARS_FOR_FLOAT);
      know (flen > 0);
      if (err)
	{
	  as_bad (_("bad floating literal: %s"), err);
	  ignore_rest_of_line ();
	  if (flag_mri)
	    mri_comment_end (stop, stopc);
	  return;
	}
    }

  while (--count >= 0)
    {
      char *p;

      p = frag_more (flen);
      memcpy (p, temp, (unsigned int) flen);
    }

  demand_empty_rest_of_line ();

  if (flag_mri)
    mri_comment_end (stop, stopc);
}