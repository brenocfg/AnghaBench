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
struct TYPE_3__ {int non_integral_constant_expression_p; int /*<<< orphan*/  allow_non_integral_constant_expression_p; scalar_t__ integral_constant_expression_p; } ;
typedef  TYPE_1__ cp_parser ;

/* Variables and functions */
 int /*<<< orphan*/  error (char*,char const*) ; 

__attribute__((used)) static bool
cp_parser_non_integral_constant_expression (cp_parser  *parser,
					    const char *thing)
{
  parser->non_integral_constant_expression_p = true;
  if (parser->integral_constant_expression_p)
    {
      if (!parser->allow_non_integral_constant_expression_p)
	{
	  error ("%s cannot appear in a constant-expression", thing);
	  return true;
	}
    }
  return false;
}