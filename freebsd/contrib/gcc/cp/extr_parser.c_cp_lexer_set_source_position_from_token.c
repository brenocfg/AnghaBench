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
struct TYPE_3__ {scalar_t__ type; int /*<<< orphan*/  input_file_stack_index; int /*<<< orphan*/  in_system_header; int /*<<< orphan*/  location; } ;
typedef  TYPE_1__ cp_token ;

/* Variables and functions */
 scalar_t__ CPP_EOF ; 
 int /*<<< orphan*/  in_system_header ; 
 int /*<<< orphan*/  input_location ; 
 int /*<<< orphan*/  restore_input_file_stack (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
cp_lexer_set_source_position_from_token (cp_token *token)
{
  if (token->type != CPP_EOF)
    {
      input_location = token->location;
      in_system_header = token->in_system_header;
      restore_input_file_stack (token->input_file_stack_index);
    }
}