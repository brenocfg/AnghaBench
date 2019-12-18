#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  len; int /*<<< orphan*/  text; } ;
struct TYPE_8__ {TYPE_1__ str; int /*<<< orphan*/  node; int /*<<< orphan*/  arg_no; } ;
struct TYPE_9__ {scalar_t__ type; scalar_t__ flags; TYPE_2__ val; } ;
typedef  TYPE_3__ cpp_token ;

/* Variables and functions */
 scalar_t__ CPP_MACRO_ARG ; 
#define  SPELL_IDENT 131 
#define  SPELL_LITERAL 130 
#define  SPELL_NONE 129 
#define  SPELL_OPERATOR 128 
 int TOKEN_SPELL (TYPE_3__ const*) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
_cpp_equiv_tokens (const cpp_token *a, const cpp_token *b)
{
  if (a->type == b->type && a->flags == b->flags)
    switch (TOKEN_SPELL (a))
      {
      default:			/* Keep compiler happy.  */
      case SPELL_OPERATOR:
	return 1;
      case SPELL_NONE:
	return (a->type != CPP_MACRO_ARG || a->val.arg_no == b->val.arg_no);
      case SPELL_IDENT:
	return a->val.node == b->val.node;
      case SPELL_LITERAL:
	return (a->val.str.len == b->val.str.len
		&& !memcmp (a->val.str.text, b->val.str.text,
			    a->val.str.len));
      }

  return 0;
}