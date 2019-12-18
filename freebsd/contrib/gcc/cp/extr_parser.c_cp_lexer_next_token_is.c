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
typedef  int /*<<< orphan*/  cp_lexer ;
struct TYPE_2__ {int type; } ;

/* Variables and functions */
 TYPE_1__* cp_lexer_peek_token (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool
cp_lexer_next_token_is (cp_lexer* lexer, enum cpp_ttype type)
{
  return cp_lexer_peek_token (lexer)->type == type;
}