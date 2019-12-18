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
struct TYPE_4__ {scalar_t__ type; int flags; } ;
typedef  TYPE_1__ cpp_token ;
typedef  int /*<<< orphan*/  cpp_reader ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ CPP_EOF ; 
 int PREV_WHITE ; 
 TYPE_1__* cpp_get_token (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpp_output_token (TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ *) ; 

void
cpp_output_line (cpp_reader *pfile, FILE *fp)
{
  const cpp_token *token;

  token = cpp_get_token (pfile);
  while (token->type != CPP_EOF)
    {
      cpp_output_token (token, fp);
      token = cpp_get_token (pfile);
      if (token->flags & PREV_WHITE)
	putc (' ', fp);
    }

  putc ('\n', fp);
}