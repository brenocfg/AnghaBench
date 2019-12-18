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
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  cp_parser ;

/* Variables and functions */
 int /*<<< orphan*/  begin_function_body () ; 
 int cp_parser_ctor_initializer_opt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cp_parser_function_body (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  finish_function_body (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
cp_parser_ctor_initializer_opt_and_function_body (cp_parser *parser)
{
  tree body;
  bool ctor_initializer_p;

  /* Begin the function body.  */
  body = begin_function_body ();
  /* Parse the optional ctor-initializer.  */
  ctor_initializer_p = cp_parser_ctor_initializer_opt (parser);
  /* Parse the function-body.  */
  cp_parser_function_body (parser);
  /* Finish the function body.  */
  finish_function_body (body);

  return ctor_initializer_p;
}