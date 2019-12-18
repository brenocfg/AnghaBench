#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct pred_data {scalar_t__* codes; } ;
struct TYPE_8__ {TYPE_1__* first; } ;
struct decision {int need_label; int number; struct decision* next; TYPE_2__ success; TYPE_5__* tests; int /*<<< orphan*/  afterward; } ;
typedef  enum decision_type { ____Placeholder_decision_type } decision_type ;
typedef  int /*<<< orphan*/  codemap ;
struct TYPE_9__ {struct pred_data* data; } ;
struct TYPE_10__ {size_t code; int veclen; int /*<<< orphan*/  intval; int /*<<< orphan*/  mode; TYPE_3__ pred; } ;
struct TYPE_11__ {int type; TYPE_4__ u; scalar_t__ next; } ;
struct TYPE_7__ {int number; int need_label; } ;
typedef  size_t RTX_CODE ;

/* Variables and functions */
 int DT_code ; 
#define  DT_elt_one_int 133 
#define  DT_elt_zero_int 132 
#define  DT_elt_zero_wide 131 
#define  DT_elt_zero_wide_safe 130 
#define  DT_mode 129 
 int DT_pred ; 
#define  DT_veclen 128 
 char* GET_MODE_NAME (int /*<<< orphan*/ ) ; 
 int NUM_RTX_CODE ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ nodes_identical_1 (TYPE_5__*,TYPE_5__*) ; 
 int /*<<< orphan*/  print_code (size_t) ; 
 int /*<<< orphan*/  print_host_wide_int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  write_afterward (struct decision*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static struct decision *
write_switch (struct decision *start, int depth)
{
  struct decision *p = start;
  enum decision_type type = p->tests->type;
  struct decision *needs_label = NULL;

  /* If we have two or more nodes in sequence that test the same one
     thing, we may be able to use a switch statement.  */

  if (!p->next
      || p->tests->next
      || p->next->tests->type != type
      || p->next->tests->next
      || nodes_identical_1 (p->tests, p->next->tests))
    return p;

  /* DT_code is special in that we can do interesting things with
     known predicates at the same time.  */
  if (type == DT_code)
    {
      char codemap[NUM_RTX_CODE];
      struct decision *ret;
      RTX_CODE code;

      memset (codemap, 0, sizeof(codemap));

      printf ("  switch (GET_CODE (x%d))\n    {\n", depth);
      code = p->tests->u.code;
      do
	{
	  if (p != start && p->need_label && needs_label == NULL)
	    needs_label = p;

	  printf ("    case ");
	  print_code (code);
	  printf (":\n      goto L%d;\n", p->success.first->number);
	  p->success.first->need_label = 1;

	  codemap[code] = 1;
	  p = p->next;
	}
      while (p
	     && ! p->tests->next
	     && p->tests->type == DT_code
	     && ! codemap[code = p->tests->u.code]);

      /* If P is testing a predicate that we know about and we haven't
	 seen any of the codes that are valid for the predicate, we can
	 write a series of "case" statement, one for each possible code.
	 Since we are already in a switch, these redundant tests are very
	 cheap and will reduce the number of predicates called.  */

      /* Note that while we write out cases for these predicates here,
	 we don't actually write the test here, as it gets kinda messy.
	 It is trivial to leave this to later by telling our caller that
	 we only processed the CODE tests.  */
      if (needs_label != NULL)
	ret = needs_label;
      else
	ret = p;

      while (p && p->tests->type == DT_pred && p->tests->u.pred.data)
	{
	  const struct pred_data *data = p->tests->u.pred.data;
	  RTX_CODE c;
	  for (c = 0; c < NUM_RTX_CODE; c++)
	    if (codemap[c] && data->codes[c])
	      goto pred_done;

	  for (c = 0; c < NUM_RTX_CODE; c++)
	    if (data->codes[c])
	      {
		fputs ("    case ", stdout);
		print_code (c);
		fputs (":\n", stdout);
		codemap[c] = 1;
	      }

	  printf ("      goto L%d;\n", p->number);
	  p->need_label = 1;
	  p = p->next;
	}

    pred_done:
      /* Make the default case skip the predicates we managed to match.  */

      printf ("    default:\n");
      if (p != ret)
	{
	  if (p)
	    {
	      printf ("      goto L%d;\n", p->number);
	      p->need_label = 1;
	    }
	  else
	    write_afterward (start, start->afterward, "      ");
	}
      else
	printf ("     break;\n");
      printf ("   }\n");

      return ret;
    }
  else if (type == DT_mode
	   || type == DT_veclen
	   || type == DT_elt_zero_int
	   || type == DT_elt_one_int
	   || type == DT_elt_zero_wide_safe)
    {
      const char *indent = "";

      /* We cast switch parameter to integer, so we must ensure that the value
	 fits.  */
      if (type == DT_elt_zero_wide_safe)
	{
	  indent = "  ";
	  printf("  if ((int) XWINT (x%d, 0) == XWINT (x%d, 0))\n", depth, depth);
	}
      printf ("%s  switch (", indent);
      switch (type)
	{
	case DT_mode:
	  printf ("GET_MODE (x%d)", depth);
	  break;
	case DT_veclen:
	  printf ("XVECLEN (x%d, 0)", depth);
	  break;
	case DT_elt_zero_int:
	  printf ("XINT (x%d, 0)", depth);
	  break;
	case DT_elt_one_int:
	  printf ("XINT (x%d, 1)", depth);
	  break;
	case DT_elt_zero_wide_safe:
	  /* Convert result of XWINT to int for portability since some C
	     compilers won't do it and some will.  */
	  printf ("(int) XWINT (x%d, 0)", depth);
	  break;
	default:
	  gcc_unreachable ();
	}
      printf (")\n%s    {\n", indent);

      do
	{
	  /* Merge trees will not unify identical nodes if their
	     sub-nodes are at different levels.  Thus we must check
	     for duplicate cases.  */
	  struct decision *q;
	  for (q = start; q != p; q = q->next)
	    if (nodes_identical_1 (p->tests, q->tests))
	      goto case_done;

	  if (p != start && p->need_label && needs_label == NULL)
	    needs_label = p;

	  printf ("%s    case ", indent);
	  switch (type)
	    {
	    case DT_mode:
	      printf ("%smode", GET_MODE_NAME (p->tests->u.mode));
	      break;
	    case DT_veclen:
	      printf ("%d", p->tests->u.veclen);
	      break;
	    case DT_elt_zero_int:
	    case DT_elt_one_int:
	    case DT_elt_zero_wide:
	    case DT_elt_zero_wide_safe:
	      print_host_wide_int (p->tests->u.intval);
	      break;
	    default:
	      gcc_unreachable ();
	    }
	  printf (":\n%s      goto L%d;\n", indent, p->success.first->number);
	  p->success.first->need_label = 1;

	  p = p->next;
	}
      while (p && p->tests->type == type && !p->tests->next);

    case_done:
      printf ("%s    default:\n%s      break;\n%s    }\n",
	      indent, indent, indent);

      return needs_label != NULL ? needs_label : p;
    }
  else
    {
      /* None of the other tests are amenable.  */
      return p;
    }
}