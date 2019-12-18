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
struct symbol {int dummy; } ;
struct dwarf2_locexpr_baton {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 struct dwarf2_locexpr_baton* SYMBOL_LOCATION_BATON (struct symbol*) ; 
 int dwarf2_loc_desc_needs_frame (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
locexpr_read_needs_frame (struct symbol *symbol)
{
  struct dwarf2_locexpr_baton *dlbaton = SYMBOL_LOCATION_BATON (symbol);
  return dwarf2_loc_desc_needs_frame (dlbaton->data, dlbaton->size);
}