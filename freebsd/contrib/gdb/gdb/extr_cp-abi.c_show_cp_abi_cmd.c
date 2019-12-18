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
struct TYPE_2__ {int /*<<< orphan*/  longname; int /*<<< orphan*/  shortname; } ;

/* Variables and functions */
 TYPE_1__ current_cp_abi ; 
 int /*<<< orphan*/  ui_out_field_string (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ui_out_text (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  uiout ; 

__attribute__((used)) static void
show_cp_abi_cmd (char *args, int from_tty)
{
  ui_out_text (uiout, "The currently selected C++ ABI is \"");

  ui_out_field_string (uiout, "cp-abi", current_cp_abi.shortname);
  ui_out_text (uiout, "\" (");
  ui_out_field_string (uiout, "longname", current_cp_abi.longname);
  ui_out_text (uiout, ").\n");
}