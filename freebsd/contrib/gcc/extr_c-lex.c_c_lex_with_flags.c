#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  location_t ;
typedef  enum cpp_ttype { ____Placeholder_cpp_ttype } cpp_ttype ;
typedef  char cppchar_t ;
struct TYPE_11__ {int len; char* text; } ;
struct TYPE_12__ {int /*<<< orphan*/  pragma; TYPE_1__ str; int /*<<< orphan*/  node; } ;
struct TYPE_13__ {int type; unsigned char flags; TYPE_2__ val; int /*<<< orphan*/  src_loc; } ;
typedef  TYPE_3__ cpp_token ;

/* Variables and functions */
#define  CPP_ATSIGN 145 
 int CPP_AT_NAME ; 
#define  CPP_CHAR 144 
#define  CPP_COMMENT 143 
#define  CPP_HASH 142 
#define  CPP_HEADER_NAME 141 
#define  CPP_MACRO_ARG 140 
#define  CPP_NAME 139 
#define  CPP_NUMBER 138 
 unsigned int CPP_N_CATEGORY ; 
#define  CPP_N_FLOATING 137 
#define  CPP_N_INTEGER 136 
#define  CPP_N_INVALID 135 
#define  CPP_OTHER 134 
#define  CPP_PADDING 133 
#define  CPP_PASTE 132 
#define  CPP_PRAGMA 131 
#define  CPP_STRING 130 
#define  CPP_WCHAR 129 
#define  CPP_WSTRING 128 
 int /*<<< orphan*/  HT_IDENT_TO_GCC_IDENT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HT_NODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISGRAPH (char) ; 
 int /*<<< orphan*/  NULL_TREE ; 
 unsigned char PURE_ZERO ; 
 int /*<<< orphan*/  TV_CPP ; 
 int /*<<< orphan*/  build_int_cst (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_string (int,char*) ; 
 int /*<<< orphan*/  c_common_no_more_pch () ; 
 int /*<<< orphan*/  c_dialect_objc () ; 
 int /*<<< orphan*/  c_lex_return_raw_strings ; 
 unsigned int cpp_classify_number (int /*<<< orphan*/ ,TYPE_3__ const*) ; 
 TYPE_3__* cpp_get_token (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cpp_spell_token (int /*<<< orphan*/ ,TYPE_3__ const*,unsigned char*,int) ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  error_mark_node ; 
 int /*<<< orphan*/  errorcount ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  input_location ; 
 int /*<<< orphan*/  interpret_float (TYPE_3__ const*,unsigned int) ; 
 int /*<<< orphan*/  interpret_integer (TYPE_3__ const*,unsigned int) ; 
 int /*<<< orphan*/  lex_charconst (TYPE_3__ const*) ; 
 int lex_string (TYPE_3__ const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  objc_is_reserved_word (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_in ; 
 int /*<<< orphan*/  timevar_pop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timevar_push (int /*<<< orphan*/ ) ; 

enum cpp_ttype
c_lex_with_flags (tree *value, location_t *loc, unsigned char *cpp_flags)
{
  static bool no_more_pch;
  const cpp_token *tok;
  enum cpp_ttype type;
  unsigned char add_flags = 0;

  timevar_push (TV_CPP);
 retry:
  tok = cpp_get_token (parse_in);
  type = tok->type;

 retry_after_at:
#ifdef USE_MAPPED_LOCATION
  *loc = tok->src_loc;
#else
  *loc = input_location;
#endif
  switch (type)
    {
    case CPP_PADDING:
      goto retry;

    case CPP_NAME:
      *value = HT_IDENT_TO_GCC_IDENT (HT_NODE (tok->val.node));
      break;

    case CPP_NUMBER:
      {
	unsigned int flags = cpp_classify_number (parse_in, tok);

	switch (flags & CPP_N_CATEGORY)
	  {
	  case CPP_N_INVALID:
	    /* cpplib has issued an error.  */
	    *value = error_mark_node;
	    errorcount++;
	    break;

	  case CPP_N_INTEGER:
	    /* C++ uses '0' to mark virtual functions as pure.
	       Set PURE_ZERO to pass this information to the C++ parser.  */
	    if (tok->val.str.len == 1 && *tok->val.str.text == '0')
	      add_flags = PURE_ZERO;
	    *value = interpret_integer (tok, flags);
	    break;

	  case CPP_N_FLOATING:
	    *value = interpret_float (tok, flags);
	    break;

	  default:
	    gcc_unreachable ();
	  }
      }
      break;

    case CPP_ATSIGN:
      /* An @ may give the next token special significance in Objective-C.  */
      if (c_dialect_objc ())
	{
	  location_t atloc = input_location;

	retry_at:
	  tok = cpp_get_token (parse_in);
	  type = tok->type;
	  switch (type)
	    {
	    case CPP_PADDING:
	      goto retry_at;

	    case CPP_STRING:
	    case CPP_WSTRING:
	      type = lex_string (tok, value, true);
	      break;

	    case CPP_NAME:
	      *value = HT_IDENT_TO_GCC_IDENT (HT_NODE (tok->val.node));
	      if (objc_is_reserved_word (*value))
		{
		  type = CPP_AT_NAME;
		  break;
		}
	      /* FALLTHROUGH */

	    default:
	      /* ... or not.  */
	      error ("%Hstray %<@%> in program", &atloc);
	      goto retry_after_at;
	    }
	  break;
	}

      /* FALLTHROUGH */
    case CPP_HASH:
    case CPP_PASTE:
      {
	unsigned char name[4];

	*cpp_spell_token (parse_in, tok, name, true) = 0;

	error ("stray %qs in program", name);
      }

      goto retry;

    case CPP_OTHER:
      {
	cppchar_t c = tok->val.str.text[0];

	if (c == '"' || c == '\'')
	  error ("missing terminating %c character", (int) c);
	else if (ISGRAPH (c))
	  error ("stray %qc in program", (int) c);
	else
	  error ("stray %<\\%o%> in program", (int) c);
      }
      goto retry;

    case CPP_CHAR:
    case CPP_WCHAR:
      *value = lex_charconst (tok);
      break;

    case CPP_STRING:
    case CPP_WSTRING:
      if (!c_lex_return_raw_strings)
	{
	  type = lex_string (tok, value, false);
	  break;
	}
      *value = build_string (tok->val.str.len, (char *) tok->val.str.text);
      break;
      
    case CPP_PRAGMA:
      *value = build_int_cst (NULL, tok->val.pragma);
      break;

      /* These tokens should not be visible outside cpplib.  */
    case CPP_HEADER_NAME:
    case CPP_COMMENT:
    case CPP_MACRO_ARG:
      gcc_unreachable ();

    default:
      *value = NULL_TREE;
      break;
    }

  if (cpp_flags)
    *cpp_flags = tok->flags | add_flags;

  if (!no_more_pch)
    {
      no_more_pch = true;
      c_common_no_more_pch ();
    }

  timevar_pop (TV_CPP);

  return type;
}