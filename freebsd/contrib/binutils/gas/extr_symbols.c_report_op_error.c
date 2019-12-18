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
typedef  int /*<<< orphan*/  symbolS ;
typedef  scalar_t__ segT ;

/* Variables and functions */
 int /*<<< orphan*/  S_GET_NAME (int /*<<< orphan*/ *) ; 
 scalar_t__ S_GET_SEGMENT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  as_bad (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  as_bad_where (char*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 scalar_t__ expr_symbol_where (int /*<<< orphan*/ *,char**,unsigned int*) ; 
 scalar_t__ undefined_section ; 

__attribute__((used)) static void
report_op_error (symbolS *symp, symbolS *left, symbolS *right)
{
  char *file;
  unsigned int line;
  segT seg_left = S_GET_SEGMENT (left);
  segT seg_right = right ? S_GET_SEGMENT (right) : 0;

  if (expr_symbol_where (symp, &file, &line))
    {
      if (seg_left == undefined_section)
	as_bad_where (file, line,
		      _("undefined symbol `%s' in operation"),
		      S_GET_NAME (left));
      if (seg_right == undefined_section)
	as_bad_where (file, line,
		      _("undefined symbol `%s' in operation"),
		      S_GET_NAME (right));
      if (seg_left != undefined_section
	  && seg_right != undefined_section)
	{
	  if (right)
	    as_bad_where (file, line,
			  _("invalid sections for operation on `%s' and `%s'"),
			  S_GET_NAME (left), S_GET_NAME (right));
	  else
	    as_bad_where (file, line,
			  _("invalid section for operation on `%s'"),
			  S_GET_NAME (left));
	}

    }
  else
    {
      if (seg_left == undefined_section)
	as_bad (_("undefined symbol `%s' in operation setting `%s'"),
		S_GET_NAME (left), S_GET_NAME (symp));
      if (seg_right == undefined_section)
	as_bad (_("undefined symbol `%s' in operation setting `%s'"),
		S_GET_NAME (right), S_GET_NAME (symp));
      if (seg_left != undefined_section
	  && seg_right != undefined_section)
	{
	  if (right)
	    as_bad (_("invalid sections for operation on `%s' and `%s' setting `%s'"),
		    S_GET_NAME (left), S_GET_NAME (right), S_GET_NAME (symp));
	  else
	    as_bad (_("invalid section for operation on `%s' setting `%s'"),
		    S_GET_NAME (left), S_GET_NAME (symp));
	}
    }
}