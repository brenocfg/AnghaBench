#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct TYPE_7__ {int /*<<< orphan*/  lexer; } ;
typedef  TYPE_2__ cp_parser ;
struct TYPE_6__ {int /*<<< orphan*/  value; } ;
struct TYPE_9__ {TYPE_1__ u; } ;
struct TYPE_8__ {int keyword; } ;

/* Variables and functions */
 int /*<<< orphan*/  NULL_TREE ; 
#define  RID_AUTO 133 
#define  RID_EXTERN 132 
#define  RID_MUTABLE 131 
#define  RID_REGISTER 130 
#define  RID_STATIC 129 
#define  RID_THREAD 128 
 TYPE_5__* cp_lexer_consume_token (int /*<<< orphan*/ ) ; 
 TYPE_4__* cp_lexer_peek_token (int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
cp_parser_storage_class_specifier_opt (cp_parser* parser)
{
  switch (cp_lexer_peek_token (parser->lexer)->keyword)
    {
    case RID_AUTO:
    case RID_REGISTER:
    case RID_STATIC:
    case RID_EXTERN:
    case RID_MUTABLE:
    case RID_THREAD:
      /* Consume the token.  */
      return cp_lexer_consume_token (parser->lexer)->u.value;

    default:
      return NULL_TREE;
    }
}