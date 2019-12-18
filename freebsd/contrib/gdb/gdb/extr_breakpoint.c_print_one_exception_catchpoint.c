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
struct breakpoint {int /*<<< orphan*/  addr_string; TYPE_1__* loc; } ;
struct TYPE_2__ {int /*<<< orphan*/  address; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 scalar_t__ addressprint ; 
 int /*<<< orphan*/  annotate_field (int) ; 
 int /*<<< orphan*/ * strstr (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ui_out_field_core_addr (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ui_out_field_string (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  uiout ; 

__attribute__((used)) static void
print_one_exception_catchpoint (struct breakpoint *b, CORE_ADDR *last_addr)
{
  if (addressprint)
    {
      annotate_field (4);
      ui_out_field_core_addr (uiout, "addr", b->loc->address);
    }
  annotate_field (5);
  *last_addr = b->loc->address;
  if (strstr (b->addr_string, "throw") != NULL)
    ui_out_field_string (uiout, "what", "exception throw");
  else
    ui_out_field_string (uiout, "what", "exception catch");
}