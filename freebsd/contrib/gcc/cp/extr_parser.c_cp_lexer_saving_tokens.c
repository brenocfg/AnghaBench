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
struct TYPE_3__ {int /*<<< orphan*/  saved_tokens; } ;
typedef  TYPE_1__ cp_lexer ;

/* Variables and functions */
 scalar_t__ VEC_length (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_token_position ; 

__attribute__((used)) static inline int
cp_lexer_saving_tokens (const cp_lexer* lexer)
{
  return VEC_length (cp_token_position, lexer->saved_tokens) != 0;
}