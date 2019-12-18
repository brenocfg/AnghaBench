#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cppchar_t ;
struct TYPE_12__ {size_t len; scalar_t__ text; } ;
struct TYPE_9__ {TYPE_6__ str; } ;
struct TYPE_10__ {scalar_t__ type; TYPE_1__ val; } ;
typedef  TYPE_2__ cpp_token ;
struct TYPE_11__ {scalar_t__ text; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ cpp_string ;
typedef  int /*<<< orphan*/  cpp_reader ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_DL_ERROR ; 
 scalar_t__ CPP_WCHAR ; 
 int /*<<< orphan*/  cpp_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cpp_interpret_string (int /*<<< orphan*/ *,TYPE_6__*,int,TYPE_3__*,int) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  narrow_str_to_charconst (int /*<<< orphan*/ *,TYPE_3__,unsigned int*,int*) ; 
 int /*<<< orphan*/  wide_str_to_charconst (int /*<<< orphan*/ *,TYPE_3__,unsigned int*,int*) ; 

cppchar_t
cpp_interpret_charconst (cpp_reader *pfile, const cpp_token *token,
			 unsigned int *pchars_seen, int *unsignedp)
{
  cpp_string str = { 0, 0 };
  bool wide = (token->type == CPP_WCHAR);
  cppchar_t result;

  /* an empty constant will appear as L'' or '' */
  if (token->val.str.len == (size_t) (2 + wide))
    {
      cpp_error (pfile, CPP_DL_ERROR, "empty character constant");
      return 0;
    }
  else if (!cpp_interpret_string (pfile, &token->val.str, 1, &str, wide))
    return 0;

  if (wide)
    result = wide_str_to_charconst (pfile, str, pchars_seen, unsignedp);
  else
    result = narrow_str_to_charconst (pfile, str, pchars_seen, unsignedp);

  if (str.text != token->val.str.text)
    free ((void *)str.text);

  return result;
}