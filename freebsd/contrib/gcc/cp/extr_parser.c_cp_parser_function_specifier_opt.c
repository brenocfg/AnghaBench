#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct TYPE_9__ {int /*<<< orphan*/  lexer; } ;
typedef  TYPE_2__ cp_parser ;
struct TYPE_10__ {int /*<<< orphan*/ * specs; } ;
typedef  TYPE_3__ cp_decl_specifier_seq ;
struct TYPE_8__ {int /*<<< orphan*/  value; } ;
struct TYPE_12__ {TYPE_1__ u; } ;
struct TYPE_11__ {int keyword; } ;

/* Variables and functions */
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  PROCESSING_REAL_TEMPLATE_DECL_P () ; 
#define  RID_EXPLICIT 130 
#define  RID_INLINE 129 
#define  RID_VIRTUAL 128 
 TYPE_7__* cp_lexer_consume_token (int /*<<< orphan*/ ) ; 
 TYPE_6__* cp_lexer_peek_token (int /*<<< orphan*/ ) ; 
 scalar_t__ ds_explicit ; 
 scalar_t__ ds_inline ; 
 scalar_t__ ds_virtual ; 
 int /*<<< orphan*/  error (char*) ; 

__attribute__((used)) static tree
cp_parser_function_specifier_opt (cp_parser* parser,
				  cp_decl_specifier_seq *decl_specs)
{
  switch (cp_lexer_peek_token (parser->lexer)->keyword)
    {
    case RID_INLINE:
      if (decl_specs)
	++decl_specs->specs[(int) ds_inline];
      break;

    case RID_VIRTUAL:
      /* 14.5.2.3 [temp.mem]

	 A member function template shall not be virtual.  */
      if (PROCESSING_REAL_TEMPLATE_DECL_P ())
	error ("templates may not be %<virtual%>");
      else if (decl_specs)
	++decl_specs->specs[(int) ds_virtual];
      break;

    case RID_EXPLICIT:
      if (decl_specs)
	++decl_specs->specs[(int) ds_explicit];
      break;

    default:
      return NULL_TREE;
    }

  /* Consume the token.  */
  return cp_lexer_consume_token (parser->lexer)->u.value;
}