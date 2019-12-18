#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* buffer; } ;
typedef  TYPE_2__ pretty_printer ;
struct TYPE_5__ {int /*<<< orphan*/  obstack; } ;

/* Variables and functions */
 int /*<<< orphan*/  obstack_1grow (int /*<<< orphan*/ ,char) ; 
 char const* pp_formatted_text_data (TYPE_2__*) ; 

const char *
pp_base_formatted_text (pretty_printer *pp)
{
  obstack_1grow (pp->buffer->obstack, '\0');
  return pp_formatted_text_data (pp);
}