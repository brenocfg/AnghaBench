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
struct expression {int dummy; } ;
struct cleanup {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  evaluate_expression (struct expression*) ; 
 int /*<<< orphan*/  free_current_contents ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,struct expression**) ; 
 struct expression* parse_expression (char*) ; 

__attribute__((used)) static void
set_command (char *exp, int from_tty)
{
  struct expression *expr = parse_expression (exp);
  struct cleanup *old_chain =
    make_cleanup (free_current_contents, &expr);
  evaluate_expression (expr);
  do_cleanups (old_chain);
}