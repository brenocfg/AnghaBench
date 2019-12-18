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
struct cleanup {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  doc; int /*<<< orphan*/  shortname; } ;

/* Variables and functions */
 TYPE_1__** cp_abis ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 struct cleanup* make_cleanup_ui_out_tuple_begin_end (int /*<<< orphan*/ ,char*) ; 
 int num_cp_abis ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ui_out_field_string (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ui_out_text (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  uiout ; 

__attribute__((used)) static void
list_cp_abis (int from_tty)
{
  struct cleanup *cleanup_chain;
  int i;
  ui_out_text (uiout, "The available C++ ABIs are:\n");

  cleanup_chain = make_cleanup_ui_out_tuple_begin_end (uiout, "cp-abi-list");
  for (i = 0; i < num_cp_abis; i++)
    {
      char pad[14];
      int padcount;

      ui_out_text (uiout, "  ");
      ui_out_field_string (uiout, "cp-abi", cp_abis[i]->shortname);

      padcount = 16 - 2 - strlen (cp_abis[i]->shortname);
      pad[padcount] = 0;
      while (padcount > 0)
	pad[--padcount] = ' ';
      ui_out_text (uiout, pad);

      ui_out_field_string (uiout, "doc", cp_abis[i]->doc);
      ui_out_text (uiout, "\n");
    }
  do_cleanups (cleanup_chain);
}