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
struct TYPE_4__ {int /*<<< orphan*/  next_token; int /*<<< orphan*/  saved_tokens; } ;
typedef  TYPE_1__ cp_lexer ;

/* Variables and functions */
 int /*<<< orphan*/  VEC_safe_push (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_lexer_debug_stream ; 
 scalar_t__ cp_lexer_debugging_p (TYPE_1__*) ; 
 int /*<<< orphan*/  cp_token_position ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  heap ; 

__attribute__((used)) static void
cp_lexer_save_tokens (cp_lexer* lexer)
{
  /* Provide debugging output.  */
  if (cp_lexer_debugging_p (lexer))
    fprintf (cp_lexer_debug_stream, "cp_lexer: saving tokens\n");

  VEC_safe_push (cp_token_position, heap,
		 lexer->saved_tokens, lexer->next_token);
}