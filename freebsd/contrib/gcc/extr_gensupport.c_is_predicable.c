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
struct queue_elem {int /*<<< orphan*/  lineno; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  rtx ;
typedef  int /*<<< orphan*/  rtvec ;

/* Variables and functions */
 int ATTR ; 
 int CONST_STRING ; 
 int GET_CODE (int /*<<< orphan*/ ) ; 
 int GET_NUM_ELEM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTVEC_ELT (int /*<<< orphan*/ ,int) ; 
#define  SET 130 
#define  SET_ATTR 129 
#define  SET_ATTR_ALTERNATIVE 128 
 int /*<<< orphan*/  SET_DEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_SRC (int /*<<< orphan*/ ) ; 
 char const* XSTR (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XVEC (int /*<<< orphan*/ ,int) ; 
 int errors ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  message_with_line (int /*<<< orphan*/ ,char*,...) ; 
 int predicable_default ; 
 char* predicable_false ; 
 char* predicable_true ; 
 int /*<<< orphan*/ * strchr (char const*,char) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int
is_predicable (struct queue_elem *elem)
{
  rtvec vec = XVEC (elem->data, 4);
  const char *value;
  int i;

  if (! vec)
    return predicable_default;

  for (i = GET_NUM_ELEM (vec) - 1; i >= 0; --i)
    {
      rtx sub = RTVEC_ELT (vec, i);
      switch (GET_CODE (sub))
	{
	case SET_ATTR:
	  if (strcmp (XSTR (sub, 0), "predicable") == 0)
	    {
	      value = XSTR (sub, 1);
	      goto found;
	    }
	  break;

	case SET_ATTR_ALTERNATIVE:
	  if (strcmp (XSTR (sub, 0), "predicable") == 0)
	    {
	      message_with_line (elem->lineno,
				 "multiple alternatives for `predicable'");
	      errors = 1;
	      return 0;
	    }
	  break;

	case SET:
	  if (GET_CODE (SET_DEST (sub)) != ATTR
	      || strcmp (XSTR (SET_DEST (sub), 0), "predicable") != 0)
	    break;
	  sub = SET_SRC (sub);
	  if (GET_CODE (sub) == CONST_STRING)
	    {
	      value = XSTR (sub, 0);
	      goto found;
	    }

	  /* ??? It would be possible to handle this if we really tried.
	     It's not easy though, and I'm not going to bother until it
	     really proves necessary.  */
	  message_with_line (elem->lineno,
			     "non-constant value for `predicable'");
	  errors = 1;
	  return 0;

	default:
	  gcc_unreachable ();
	}
    }

  return predicable_default;

 found:
  /* Verify that predicability does not vary on the alternative.  */
  /* ??? It should be possible to handle this by simply eliminating
     the non-predicable alternatives from the insn.  FRV would like
     to do this.  Delay this until we've got the basics solid.  */
  if (strchr (value, ',') != NULL)
    {
      message_with_line (elem->lineno,
			 "multiple alternatives for `predicable'");
      errors = 1;
      return 0;
    }

  /* Find out which value we're looking at.  */
  if (strcmp (value, predicable_true) == 0)
    return 1;
  if (strcmp (value, predicable_false) == 0)
    return 0;

  message_with_line (elem->lineno,
		     "unknown value `%s' for `predicable' attribute",
		     value);
  errors = 1;
  return 0;
}