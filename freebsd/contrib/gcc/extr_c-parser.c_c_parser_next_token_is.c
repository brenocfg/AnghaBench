#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  enum cpp_ttype { ____Placeholder_cpp_ttype } cpp_ttype ;
typedef  int /*<<< orphan*/  c_parser ;
struct TYPE_2__ {int type; } ;

/* Variables and functions */
 TYPE_1__* c_parser_peek_token (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool
c_parser_next_token_is (c_parser *parser, enum cpp_ttype type)
{
  return c_parser_peek_token (parser)->type == type;
}