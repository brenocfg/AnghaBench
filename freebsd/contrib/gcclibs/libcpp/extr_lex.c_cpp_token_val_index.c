#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  enum cpp_token_fld_kind { ____Placeholder_cpp_token_fld_kind } cpp_token_fld_kind ;
struct TYPE_4__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ cpp_token ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_MACRO_ARG ; 
 int /*<<< orphan*/  CPP_PADDING ; 
 int /*<<< orphan*/  CPP_PRAGMA ; 
 int CPP_TOKEN_FLD_ARG_NO ; 
 int CPP_TOKEN_FLD_NODE ; 
 int CPP_TOKEN_FLD_NONE ; 
 int CPP_TOKEN_FLD_PRAGMA ; 
 int CPP_TOKEN_FLD_SOURCE ; 
 int CPP_TOKEN_FLD_STR ; 
#define  SPELL_IDENT 130 
#define  SPELL_LITERAL 129 
#define  SPELL_NONE 128 
 int TOKEN_SPELL (TYPE_1__*) ; 

enum cpp_token_fld_kind
cpp_token_val_index (cpp_token *tok)
{
  switch (TOKEN_SPELL (tok))
    {
    case SPELL_IDENT:
      return CPP_TOKEN_FLD_NODE;
    case SPELL_LITERAL:
      return CPP_TOKEN_FLD_STR;
    case SPELL_NONE:
      if (tok->type == CPP_MACRO_ARG)
	return CPP_TOKEN_FLD_ARG_NO;
      else if (tok->type == CPP_PADDING)
	return CPP_TOKEN_FLD_SOURCE;
      else if (tok->type == CPP_PRAGMA)
	return CPP_TOKEN_FLD_PRAGMA;
      /* else fall through */
    default:
      return CPP_TOKEN_FLD_NONE;
    }
}