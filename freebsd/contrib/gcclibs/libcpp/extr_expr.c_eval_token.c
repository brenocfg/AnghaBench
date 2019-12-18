#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
typedef  int cppchar_t ;
typedef  int /*<<< orphan*/  cppchar_signed_t ;
struct TYPE_26__ {int /*<<< orphan*/  node; } ;
struct TYPE_27__ {int type; TYPE_3__ val; } ;
typedef  TYPE_4__ cpp_token ;
struct TYPE_25__ {int /*<<< orphan*/  skip_eval; } ;
struct TYPE_24__ {int /*<<< orphan*/  n_true; int /*<<< orphan*/  n_false; int /*<<< orphan*/  n_defined; } ;
struct TYPE_28__ {TYPE_2__ state; TYPE_1__ spec_nodes; } ;
typedef  TYPE_5__ cpp_reader ;
typedef  int cpp_num_part ;
struct TYPE_29__ {int unsignedp; int overflow; int high; int low; } ;
typedef  TYPE_6__ cpp_num ;

/* Variables and functions */
 int BITS_PER_CPPCHAR_T ; 
#define  CPP_CHAR 134 
 int /*<<< orphan*/  CPP_DL_ERROR ; 
 int /*<<< orphan*/  CPP_DL_WARNING ; 
#define  CPP_NAME 133 
#define  CPP_NUMBER 132 
 unsigned int CPP_N_CATEGORY ; 
#define  CPP_N_FLOATING 131 
 unsigned int CPP_N_IMAGINARY ; 
#define  CPP_N_INTEGER 130 
#define  CPP_N_INVALID 129 
 int /*<<< orphan*/  CPP_OPTION (TYPE_5__*,int /*<<< orphan*/ ) ; 
#define  CPP_WCHAR 128 
 int /*<<< orphan*/  NODE_NAME (int /*<<< orphan*/ ) ; 
 int PART_PRECISION ; 
 int /*<<< orphan*/  _cpp_test_assertion (TYPE_5__*,unsigned int*) ; 
 int /*<<< orphan*/  cplusplus ; 
 unsigned int cpp_classify_number (TYPE_5__*,TYPE_4__ const*) ; 
 int /*<<< orphan*/  cpp_error (TYPE_5__*,int /*<<< orphan*/ ,char*,...) ; 
 int cpp_interpret_charconst (TYPE_5__*,TYPE_4__ const*,unsigned int*,int*) ; 
 TYPE_6__ cpp_interpret_integer (TYPE_5__*,TYPE_4__ const*,unsigned int) ; 
 TYPE_6__ num_trim (TYPE_6__,int /*<<< orphan*/ ) ; 
 TYPE_6__ parse_defined (TYPE_5__*) ; 
 int /*<<< orphan*/  precision ; 
 int /*<<< orphan*/  warn_undef ; 

__attribute__((used)) static cpp_num
eval_token (cpp_reader *pfile, const cpp_token *token)
{
  cpp_num result;
  unsigned int temp;
  int unsignedp = 0;

  result.unsignedp = false;
  result.overflow = false;

  switch (token->type)
    {
    case CPP_NUMBER:
      temp = cpp_classify_number (pfile, token);
      switch (temp & CPP_N_CATEGORY)
	{
	case CPP_N_FLOATING:
	  cpp_error (pfile, CPP_DL_ERROR,
		     "floating constant in preprocessor expression");
	  break;
	case CPP_N_INTEGER:
	  if (!(temp & CPP_N_IMAGINARY))
	    return cpp_interpret_integer (pfile, token, temp);
	  cpp_error (pfile, CPP_DL_ERROR,
		     "imaginary number in preprocessor expression");
	  break;

	case CPP_N_INVALID:
	  /* Error already issued.  */
	  break;
	}
      result.high = result.low = 0;
      break;

    case CPP_WCHAR:
    case CPP_CHAR:
      {
	cppchar_t cc = cpp_interpret_charconst (pfile, token,
						&temp, &unsignedp);

	result.high = 0;
	result.low = cc;
	/* Sign-extend the result if necessary.  */
	if (!unsignedp && (cppchar_signed_t) cc < 0)
	  {
	    if (PART_PRECISION > BITS_PER_CPPCHAR_T)
	      result.low |= ~(~(cpp_num_part) 0
			      >> (PART_PRECISION - BITS_PER_CPPCHAR_T));
	    result.high = ~(cpp_num_part) 0;
	    result = num_trim (result, CPP_OPTION (pfile, precision));
	  }
      }
      break;

    case CPP_NAME:
      if (token->val.node == pfile->spec_nodes.n_defined)
	return parse_defined (pfile);
      else if (CPP_OPTION (pfile, cplusplus)
	       && (token->val.node == pfile->spec_nodes.n_true
		   || token->val.node == pfile->spec_nodes.n_false))
	{
	  result.high = 0;
	  result.low = (token->val.node == pfile->spec_nodes.n_true);
	}
      else
	{
	  result.high = 0;
	  result.low = 0;
	  if (CPP_OPTION (pfile, warn_undef) && !pfile->state.skip_eval)
	    cpp_error (pfile, CPP_DL_WARNING, "\"%s\" is not defined",
		       NODE_NAME (token->val.node));
	}
      break;

    default: /* CPP_HASH */
      _cpp_test_assertion (pfile, &temp);
      result.high = 0;
      result.low = temp;
    }

  result.unsignedp = !!unsignedp;
  return result;
}