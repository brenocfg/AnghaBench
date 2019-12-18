#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int maximum_length; TYPE_1__* buffer; } ;
typedef  TYPE_2__ pretty_printer ;
struct TYPE_4__ {int line_length; } ;

/* Variables and functions */

int
pp_base_remaining_character_count_for_line (pretty_printer *pp)
{
  return pp->maximum_length - pp->buffer->line_length;
}