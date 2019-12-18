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
struct work_stuff {int dummy; } ;
typedef  int /*<<< orphan*/  string ;

/* Variables and functions */
 int INTBUF_SIZE ; 
 int consume_count (char const**) ; 
 int consume_count_with_underscores (char const**) ; 
 int demangle_expression (struct work_stuff*,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int demangle_qualified (struct work_stuff*,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  string_append (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  string_appendn (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  tk_integral ; 

__attribute__((used)) static int
demangle_integral_value (struct work_stuff *work,
                         const char **mangled, string *s)
{
  int success;

  if (**mangled == 'E')
    success = demangle_expression (work, mangled, s, tk_integral);
  else if (**mangled == 'Q' || **mangled == 'K')
    success = demangle_qualified (work, mangled, s, 0, 1);
  else
    {
      int value;

      /* By default, we let the number decide whether we shall consume an
	 underscore.  */
      int multidigit_without_leading_underscore = 0;
      int leave_following_underscore = 0;

      success = 0;

      if (**mangled == '_')
        {
	  if (mangled[0][1] == 'm')
	    {
	      /* Since consume_count_with_underscores does not handle the
		 `m'-prefix we must do it here, using consume_count and
		 adjusting underscores: we have to consume the underscore
		 matching the prepended one.  */
	      multidigit_without_leading_underscore = 1;
	      string_appendn (s, "-", 1);
	      (*mangled) += 2;
	    }
	  else
	    {
	      /* Do not consume a following underscore;
	         consume_count_with_underscores will consume what
	         should be consumed.  */
	      leave_following_underscore = 1;
	    }
	}
      else
	{
	  /* Negative numbers are indicated with a leading `m'.  */
	  if (**mangled == 'm')
	  {
	    string_appendn (s, "-", 1);
	    (*mangled)++;
	  }
	  /* Since consume_count_with_underscores does not handle
	     multi-digit numbers that do not start with an underscore,
	     and this number can be an integer template parameter,
	     we have to call consume_count. */
	  multidigit_without_leading_underscore = 1;
	  /* These multi-digit numbers never end on an underscore,
	     so if there is one then don't eat it. */
	  leave_following_underscore = 1;
	}

      /* We must call consume_count if we expect to remove a trailing
	 underscore, since consume_count_with_underscores expects
	 the leading underscore (that we consumed) if it is to handle
	 multi-digit numbers.  */
      if (multidigit_without_leading_underscore)
	value = consume_count (mangled);
      else
	value = consume_count_with_underscores (mangled);

      if (value != -1)
	{
	  char buf[INTBUF_SIZE];
	  sprintf (buf, "%d", value);
	  string_append (s, buf);

	  /* Numbers not otherwise delimited, might have an underscore
	     appended as a delimeter, which we should skip.

	     ??? This used to always remove a following underscore, which
	     is wrong.  If other (arbitrary) cases are followed by an
	     underscore, we need to do something more radical.  */

	  if ((value > 9 || multidigit_without_leading_underscore)
	      && ! leave_following_underscore
	      && **mangled == '_')
	    (*mangled)++;

	  /* All is well.  */
	  success = 1;
	}
      }

  return success;
}