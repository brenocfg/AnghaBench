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
typedef  int /*<<< orphan*/  tree ;
typedef  scalar_t__ cppchar_t ;
typedef  scalar_t__ cppchar_signed_t ;
struct TYPE_4__ {scalar_t__ type; } ;
typedef  TYPE_1__ cpp_token ;

/* Variables and functions */
 scalar_t__ CPP_WCHAR ; 
 int /*<<< orphan*/  build_int_cst_wide (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  c_dialect_cxx () ; 
 int /*<<< orphan*/  char_type_node ; 
 scalar_t__ cpp_interpret_charconst (int /*<<< orphan*/ ,TYPE_1__ const*,unsigned int*,int*) ; 
 int /*<<< orphan*/  integer_type_node ; 
 int /*<<< orphan*/  parse_in ; 
 int /*<<< orphan*/  wchar_type_node ; 

__attribute__((used)) static tree
lex_charconst (const cpp_token *token)
{
  cppchar_t result;
  tree type, value;
  unsigned int chars_seen;
  int unsignedp;

  result = cpp_interpret_charconst (parse_in, token,
				    &chars_seen, &unsignedp);

  if (token->type == CPP_WCHAR)
    type = wchar_type_node;
  /* In C, a character constant has type 'int'.
     In C++ 'char', but multi-char charconsts have type 'int'.  */
  else if (!c_dialect_cxx () || chars_seen > 1)
    type = integer_type_node;
  else
    type = char_type_node;

  /* Cast to cppchar_signed_t to get correct sign-extension of RESULT
     before possibly widening to HOST_WIDE_INT for build_int_cst.  */
  if (unsignedp || (cppchar_signed_t) result >= 0)
    value = build_int_cst_wide (type, result, 0);
  else
    value = build_int_cst_wide (type, (cppchar_signed_t) result, -1);

  return value;
}