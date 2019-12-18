#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* buffer; } ;
typedef  TYPE_2__ pretty_printer ;
struct TYPE_7__ {int /*<<< orphan*/  line_length; int /*<<< orphan*/  obstack; } ;

/* Variables and functions */
 scalar_t__ ISSPACE (int) ; 
 int /*<<< orphan*/  obstack_1grow (int /*<<< orphan*/ ,int) ; 
 scalar_t__ pp_is_wrapping_line (TYPE_2__*) ; 
 int /*<<< orphan*/  pp_newline (TYPE_2__*) ; 
 scalar_t__ pp_remaining_character_count_for_line (TYPE_2__*) ; 

void
pp_base_character (pretty_printer *pp, int c)
{
  if (pp_is_wrapping_line (pp)
      && pp_remaining_character_count_for_line (pp) <= 0)
    {
      pp_newline (pp);
      if (ISSPACE (c))
        return;
    }
  obstack_1grow (pp->buffer->obstack, c);
  ++pp->buffer->line_length;
}