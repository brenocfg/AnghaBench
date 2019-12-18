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

/* Variables and functions */
 int /*<<< orphan*/  error (char*) ; 
 struct expression* parse_exp_1 (char**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct expression *
parse_expression (char *string)
{
  struct expression *exp;
  exp = parse_exp_1 (&string, 0, 0);
  if (*string)
    error ("Junk after end of expression.");
  return exp;
}