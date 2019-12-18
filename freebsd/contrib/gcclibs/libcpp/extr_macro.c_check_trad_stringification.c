#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uchar ;
struct TYPE_5__ {int len; int /*<<< orphan*/ * text; } ;
typedef  TYPE_1__ cpp_string ;
typedef  int /*<<< orphan*/  cpp_reader ;
struct TYPE_6__ {unsigned int paramc; int /*<<< orphan*/ ** params; } ;
typedef  TYPE_2__ cpp_macro ;
typedef  int /*<<< orphan*/  cpp_hashnode ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_DL_WARNING ; 
 unsigned int NODE_LEN (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  NODE_NAME (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  cpp_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_idchar (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  is_idstart (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void
check_trad_stringification (cpp_reader *pfile, const cpp_macro *macro,
			    const cpp_string *string)
{
  unsigned int i, len;
  const uchar *p, *q, *limit;

  /* Loop over the string.  */
  limit = string->text + string->len - 1;
  for (p = string->text + 1; p < limit; p = q)
    {
      /* Find the start of an identifier.  */
      while (p < limit && !is_idstart (*p))
	p++;

      /* Find the end of the identifier.  */
      q = p;
      while (q < limit && is_idchar (*q))
	q++;

      len = q - p;

      /* Loop over the function macro arguments to see if the
	 identifier inside the string matches one of them.  */
      for (i = 0; i < macro->paramc; i++)
	{
	  const cpp_hashnode *node = macro->params[i];

	  if (NODE_LEN (node) == len
	      && !memcmp (p, NODE_NAME (node), len))
	    {
	      cpp_error (pfile, CPP_DL_WARNING,
	   "macro argument \"%s\" would be stringified in traditional C",
			 NODE_NAME (node));
	      break;
	    }
	}
    }
}