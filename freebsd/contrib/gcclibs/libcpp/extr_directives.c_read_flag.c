#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int len; unsigned int* text; } ;
struct TYPE_6__ {TYPE_2__ str; } ;
struct TYPE_8__ {scalar_t__ type; TYPE_1__ val; } ;
typedef  TYPE_3__ cpp_token ;
typedef  int /*<<< orphan*/  cpp_reader ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_DL_ERROR ; 
 scalar_t__ CPP_EOF ; 
 scalar_t__ CPP_NUMBER ; 
 TYPE_3__* _cpp_lex_token (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpp_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpp_token_as_text (int /*<<< orphan*/ *,TYPE_3__ const*) ; 

__attribute__((used)) static unsigned int
read_flag (cpp_reader *pfile, unsigned int last)
{
  const cpp_token *token = _cpp_lex_token (pfile);

  if (token->type == CPP_NUMBER && token->val.str.len == 1)
    {
      unsigned int flag = token->val.str.text[0] - '0';

      if (flag > last && flag <= 4
	  && (flag != 4 || last == 3)
	  && (flag != 2 || last == 0))
	return flag;
    }

  if (token->type != CPP_EOF)
    cpp_error (pfile, CPP_DL_ERROR, "invalid flag \"%s\" in line directive",
	       cpp_token_as_text (pfile, token));
  return 0;
}