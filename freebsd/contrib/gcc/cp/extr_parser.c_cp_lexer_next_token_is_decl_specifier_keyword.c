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
struct TYPE_3__ {int keyword; } ;
typedef  TYPE_1__ cp_token ;
typedef  int /*<<< orphan*/  cp_lexer ;

/* Variables and functions */
#define  RID_ATTRIBUTE 151 
#define  RID_AUTO 150 
#define  RID_BOOL 149 
#define  RID_CHAR 148 
#define  RID_CLASS 147 
#define  RID_DOUBLE 146 
#define  RID_ENUM 145 
#define  RID_EXTERN 144 
#define  RID_FLOAT 143 
#define  RID_INT 142 
#define  RID_LONG 141 
#define  RID_MUTABLE 140 
#define  RID_REGISTER 139 
#define  RID_SHORT 138 
#define  RID_SIGNED 137 
#define  RID_STATIC 136 
#define  RID_STRUCT 135 
#define  RID_THREAD 134 
#define  RID_TYPENAME 133 
#define  RID_TYPEOF 132 
#define  RID_UNION 131 
#define  RID_UNSIGNED 130 
#define  RID_VOID 129 
#define  RID_WCHAR 128 
 TYPE_1__* cp_lexer_peek_token (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
cp_lexer_next_token_is_decl_specifier_keyword (cp_lexer *lexer)
{
  cp_token *token;

  token = cp_lexer_peek_token (lexer);
  switch (token->keyword) 
    {
      /* Storage classes.  */
    case RID_AUTO:
    case RID_REGISTER:
    case RID_STATIC:
    case RID_EXTERN:
    case RID_MUTABLE:
    case RID_THREAD:
      /* Elaborated type specifiers.  */
    case RID_ENUM:
    case RID_CLASS:
    case RID_STRUCT:
    case RID_UNION:
    case RID_TYPENAME:
      /* Simple type specifiers.  */
    case RID_CHAR:
    case RID_WCHAR:
    case RID_BOOL:
    case RID_SHORT:
    case RID_INT:
    case RID_LONG:
    case RID_SIGNED:
    case RID_UNSIGNED:
    case RID_FLOAT:
    case RID_DOUBLE:
    case RID_VOID:
      /* GNU extensions.  */ 
    case RID_ATTRIBUTE:
    case RID_TYPEOF:
      return true;

    default:
      return false;
    }
}