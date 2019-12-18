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
typedef  int /*<<< orphan*/ * tree ;
typedef  enum rid { ____Placeholder_rid } rid ;
struct TYPE_4__ {int type; int keyword; int /*<<< orphan*/ * value; int /*<<< orphan*/  pragma_kind; int /*<<< orphan*/  id_kind; int /*<<< orphan*/  in_system_header; int /*<<< orphan*/  location; } ;
typedef  TYPE_1__ c_token ;
typedef  int /*<<< orphan*/  c_parser ;

/* Variables and functions */
#define  CPP_AT_NAME 134 
#define  CPP_CLOSE_PAREN 133 
#define  CPP_COLON 132 
#define  CPP_COMMA 131 
 void* CPP_KEYWORD ; 
 int const CPP_MINUS ; 
 int const CPP_MINUS_MINUS ; 
 int const CPP_MULT ; 
#define  CPP_NAME 130 
 int const CPP_OPEN_PAREN ; 
 int const CPP_OPEN_SQUARE ; 
 int const CPP_PLUS ; 
 int const CPP_PLUS_PLUS ; 
#define  CPP_PRAGMA 129 
#define  CPP_SEMICOLON 128 
 int /*<<< orphan*/  C_ID_CLASSNAME ; 
 int /*<<< orphan*/  C_ID_ID ; 
 int /*<<< orphan*/  C_ID_NONE ; 
 int /*<<< orphan*/  C_ID_TYPENAME ; 
 int /*<<< orphan*/  C_IS_RESERVED_WORD (int /*<<< orphan*/ *) ; 
 void* C_RID_CODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OBJC_IS_AT_KEYWORD (int) ; 
 int /*<<< orphan*/  OBJC_IS_PQ_KEYWORD (int) ; 
 int /*<<< orphan*/  OBJC_NEED_RAW_IDENTIFIER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRAGMA_NONE ; 
 int RID_IN ; 
 int RID_MAX ; 
 int /*<<< orphan*/  TREE_CODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TREE_INT_CST_LOW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TV_LEX ; 
 int /*<<< orphan*/  TYPE_DECL ; 
 int /*<<< orphan*/  c_dialect_objc () ; 
 int c_lex_with_flags (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* c_parser_peek_2nd_token (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  global_bindings_p () ; 
 int /*<<< orphan*/  in_system_header ; 
 int /*<<< orphan*/ * lookup_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  objc_foreach_context ; 
 int /*<<< orphan*/ * objc_is_class_name (int /*<<< orphan*/ *) ; 
 int objc_need_raw_identifier ; 
 int /*<<< orphan*/  objc_pq_context ; 
 void** ridpointers ; 
 int /*<<< orphan*/  timevar_pop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timevar_push (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
c_lex_one_token (c_token *token, c_parser *parser)
{
  timevar_push (TV_LEX);

  token->type = c_lex_with_flags (&token->value, &token->location, NULL);
  token->id_kind = C_ID_NONE;
  token->keyword = RID_MAX;
  token->pragma_kind = PRAGMA_NONE;
  token->in_system_header = in_system_header;

  switch (token->type)
    {
    case CPP_NAME:
      {
	tree decl;

	int objc_force_identifier = objc_need_raw_identifier;
	OBJC_NEED_RAW_IDENTIFIER (0);

	if (C_IS_RESERVED_WORD (token->value))
	  {
	    enum rid rid_code = C_RID_CODE (token->value);

	    if (c_dialect_objc ())
	      {
		if (!OBJC_IS_AT_KEYWORD (rid_code)
		    && (!OBJC_IS_PQ_KEYWORD (rid_code) || objc_pq_context))
		  {
		    /* Return the canonical spelling for this keyword.  */
		    token->value = ridpointers[(int) rid_code];
		    token->type = CPP_KEYWORD;
		    token->keyword = rid_code;
		    break;
		  }
		/* APPLE LOCAL begin radar 4708210 (for_objc_collection in 4.2) */
		else if (objc_foreach_context && rid_code == RID_IN)
		  {
		    /* This is dangerous, we assume we don't need 3 input tokens look ahead.  */
		    c_token *tk = c_parser_peek_2nd_token (parser);
		    if (tk->type == CPP_NAME
			|| tk->type == CPP_OPEN_PAREN
			|| tk->type == CPP_MULT
			|| tk->type == CPP_PLUS
			|| tk->type == CPP_PLUS_PLUS
			|| tk->type == CPP_MINUS
			|| tk->type == CPP_MINUS_MINUS
			/* APPLE LOCAL radar 4529200 (in 4.2 af) */
			|| tk->type == CPP_OPEN_SQUARE)
		      {
			token->type = CPP_KEYWORD;
			token->keyword = rid_code;
			break;
		      }
		  }
		/* APPLE LOCAL end radar 4708210 (for_objc_collection in 4.2) */
	      }
	    else
	      {
		/* Return the canonical spelling for this keyword.  */
		token->value = ridpointers[(int) rid_code];
		token->type = CPP_KEYWORD;
		token->keyword = rid_code;
		break;
	      }
	  }

	decl = lookup_name (token->value);
	if (decl)
	  {
	    if (TREE_CODE (decl) == TYPE_DECL)
	      {
		token->id_kind = C_ID_TYPENAME;
		break;
	      }
	  }
	else if (c_dialect_objc ())
	  {
	    tree objc_interface_decl = objc_is_class_name (token->value);
	    /* Objective-C class names are in the same namespace as
	       variables and typedefs, and hence are shadowed by local
	       declarations.  */
	    if (objc_interface_decl
		&& (global_bindings_p ()
		    || (!objc_force_identifier && !decl)))
	      {
		token->value = objc_interface_decl;
		token->id_kind = C_ID_CLASSNAME;
		break;
	      }
	  }
        token->id_kind = C_ID_ID;
      }
      break;
    case CPP_AT_NAME:
      /* This only happens in Objective-C; it must be a keyword.  */
      token->type = CPP_KEYWORD;
      token->keyword = C_RID_CODE (token->value);
      break;
    case CPP_COLON:
    case CPP_COMMA:
    case CPP_CLOSE_PAREN:
    case CPP_SEMICOLON:
      /* These tokens may affect the interpretation of any identifiers
	 following, if doing Objective-C.  */
      OBJC_NEED_RAW_IDENTIFIER (0);
      break;
    case CPP_PRAGMA:
      /* We smuggled the cpp_token->u.pragma value in an INTEGER_CST.  */
      token->pragma_kind = TREE_INT_CST_LOW (token->value);
      token->value = NULL;
      break;
    default:
      break;
    }
  timevar_pop (TV_LEX);
}