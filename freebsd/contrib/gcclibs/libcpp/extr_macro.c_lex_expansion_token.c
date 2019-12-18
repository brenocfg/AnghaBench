#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {int /*<<< orphan*/  str; TYPE_2__* node; int /*<<< orphan*/  arg_no; } ;
struct TYPE_21__ {scalar_t__ type; TYPE_3__ val; } ;
typedef  TYPE_4__ cpp_token ;
struct TYPE_22__ {TYPE_4__* cur_token; } ;
typedef  TYPE_5__ cpp_reader ;
struct TYPE_23__ {scalar_t__ paramc; } ;
typedef  TYPE_6__ cpp_macro ;
struct TYPE_18__ {int /*<<< orphan*/  arg_index; } ;
struct TYPE_19__ {int flags; TYPE_1__ value; } ;

/* Variables and functions */
 scalar_t__ CPP_CHAR ; 
 scalar_t__ CPP_MACRO_ARG ; 
 scalar_t__ CPP_NAME ; 
 scalar_t__ CPP_STRING ; 
 scalar_t__ CPP_WTRADITIONAL (TYPE_5__*) ; 
 int NODE_MACRO_ARG ; 
 TYPE_4__* _cpp_lex_direct (TYPE_5__*) ; 
 TYPE_4__* alloc_expansion_token (TYPE_5__*,TYPE_6__*) ; 
 int /*<<< orphan*/  check_trad_stringification (TYPE_5__*,TYPE_6__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static cpp_token *
lex_expansion_token (cpp_reader *pfile, cpp_macro *macro)
{
  cpp_token *token, *saved_cur_token;

  saved_cur_token = pfile->cur_token;
  pfile->cur_token = alloc_expansion_token (pfile, macro);
  token = _cpp_lex_direct (pfile);
  pfile->cur_token = saved_cur_token;

  /* Is this a parameter?  */
  if (token->type == CPP_NAME
      && (token->val.node->flags & NODE_MACRO_ARG) != 0)
    {
      token->type = CPP_MACRO_ARG;
      token->val.arg_no = token->val.node->value.arg_index;
    }
  else if (CPP_WTRADITIONAL (pfile) && macro->paramc > 0
	   && (token->type == CPP_STRING || token->type == CPP_CHAR))
    check_trad_stringification (pfile, macro, &token->val.str);

  return token;
}