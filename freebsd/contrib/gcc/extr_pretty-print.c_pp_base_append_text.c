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
struct TYPE_7__ {scalar_t__ line_length; } ;

/* Variables and functions */
 int /*<<< orphan*/  pp_append_r (TYPE_2__*,char const*,int) ; 
 int /*<<< orphan*/  pp_emit_prefix (TYPE_2__*) ; 
 scalar_t__ pp_is_wrapping_line (TYPE_2__*) ; 

void
pp_base_append_text (pretty_printer *pp, const char *start, const char *end)
{
  /* Emit prefix and skip whitespace if we're starting a new line.  */
  if (pp->buffer->line_length == 0)
    {
      pp_emit_prefix (pp);
      if (pp_is_wrapping_line (pp))
	while (start != end && *start == ' ')
	  ++start;
    }
  pp_append_r (pp, start, end - start);
}