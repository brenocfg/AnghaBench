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
typedef  int /*<<< orphan*/  c_token ;
typedef  int /*<<< orphan*/  c_parser ;

/* Variables and functions */
 int /*<<< orphan*/ * c_parser_peek_token (int /*<<< orphan*/ *) ; 
 int c_token_starts_typename (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool
c_parser_next_token_starts_typename (c_parser *parser)
{
  c_token *token = c_parser_peek_token (parser);
  return c_token_starts_typename (token);
}