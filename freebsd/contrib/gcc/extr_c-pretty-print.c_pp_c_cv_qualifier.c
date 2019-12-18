#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  c_pretty_printer ;

/* Variables and functions */
 int /*<<< orphan*/  pp_c_identifier (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  pp_c_whitespace (int /*<<< orphan*/ *) ; 
 char* pp_last_position_in_text (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pp_c_cv_qualifier (c_pretty_printer *pp, const char *cv)
{
  const char *p = pp_last_position_in_text (pp);
  /* The C programming language does not have references, but it is much
     simpler to handle those here rather than going through the same
     logic in the C++ pretty-printer.  */
  if (p != NULL && (*p == '*' || *p == '&'))
    pp_c_whitespace (pp);
  pp_c_identifier (pp, cv);
}