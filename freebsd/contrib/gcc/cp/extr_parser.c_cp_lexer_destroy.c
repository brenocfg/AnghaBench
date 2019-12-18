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
struct TYPE_4__ {int /*<<< orphan*/  saved_tokens; struct TYPE_4__* buffer; } ;
typedef  TYPE_1__ cp_lexer ;

/* Variables and functions */
 int /*<<< orphan*/  VEC_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_token_position ; 
 int /*<<< orphan*/  ggc_free (TYPE_1__*) ; 
 int /*<<< orphan*/  heap ; 

__attribute__((used)) static void
cp_lexer_destroy (cp_lexer *lexer)
{
  if (lexer->buffer)
    ggc_free (lexer->buffer);
  VEC_free (cp_token_position, heap, lexer->saved_tokens);
  ggc_free (lexer);
}