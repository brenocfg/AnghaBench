#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct TYPE_3__ {scalar_t__ type; int keyword; int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ c_token ;
typedef  int /*<<< orphan*/  c_parser ;

/* Variables and functions */
 scalar_t__ CPP_KEYWORD ; 
 scalar_t__ CPP_NAME ; 
 int /*<<< orphan*/  NULL_TREE ; 
#define  RID_ALIGNOF 166 
#define  RID_ASM 165 
#define  RID_BOOL 164 
#define  RID_BREAK 163 
#define  RID_BYCOPY 162 
#define  RID_BYREF 161 
#define  RID_CASE 160 
#define  RID_CHAR 159 
#define  RID_COMPLEX 158 
#define  RID_CONST 157 
#define  RID_CONTINUE 156 
#define  RID_DEFAULT 155 
#define  RID_DO 154 
#define  RID_DOUBLE 153 
#define  RID_ELSE 152 
#define  RID_ENUM 151 
#define  RID_FLOAT 150 
#define  RID_FOR 149 
#define  RID_GOTO 148 
#define  RID_IF 147 
#define  RID_IN 146 
#define  RID_INOUT 145 
#define  RID_INT 144 
#define  RID_LONG 143 
#define  RID_ONEWAY 142 
#define  RID_OUT 141 
#define  RID_RESTRICT 140 
#define  RID_RETURN 139 
#define  RID_SHORT 138 
#define  RID_SIGNED 137 
#define  RID_SIZEOF 136 
#define  RID_STRUCT 135 
#define  RID_SWITCH 134 
#define  RID_TYPEOF 133 
#define  RID_UNION 132 
#define  RID_UNSIGNED 131 
#define  RID_VOID 130 
#define  RID_VOLATILE 129 
#define  RID_WHILE 128 
 int /*<<< orphan*/  c_parser_consume_token (int /*<<< orphan*/ *) ; 
 TYPE_1__* c_parser_peek_token (int /*<<< orphan*/ *) ; 

__attribute__((used)) static tree
c_parser_objc_selector (c_parser *parser)
{
  c_token *token = c_parser_peek_token (parser);
  tree value = token->value;
  if (token->type == CPP_NAME)
    {
      c_parser_consume_token (parser);
      return value;
    }
  if (token->type != CPP_KEYWORD)
    return NULL_TREE;
  switch (token->keyword)
    {
    case RID_ENUM:
    case RID_STRUCT:
    case RID_UNION:
    case RID_IF:
    case RID_ELSE:
    case RID_WHILE:
    case RID_DO:
    case RID_FOR:
    case RID_SWITCH:
    case RID_CASE:
    case RID_DEFAULT:
    case RID_BREAK:
    case RID_CONTINUE:
    case RID_RETURN:
    case RID_GOTO:
    case RID_ASM:
    case RID_SIZEOF:
    case RID_TYPEOF:
    case RID_ALIGNOF:
    case RID_UNSIGNED:
    case RID_LONG:
    case RID_CONST:
    case RID_SHORT:
    case RID_VOLATILE:
    case RID_SIGNED:
    case RID_RESTRICT:
    case RID_COMPLEX:
    case RID_IN:
    case RID_OUT:
    case RID_INOUT:
    case RID_BYCOPY:
    case RID_BYREF:
    case RID_ONEWAY:
    case RID_INT:
    case RID_CHAR:
    case RID_FLOAT:
    case RID_DOUBLE:
    case RID_VOID:
    case RID_BOOL:
      c_parser_consume_token (parser);
      return value;
    default:
      return NULL_TREE;
    }
}