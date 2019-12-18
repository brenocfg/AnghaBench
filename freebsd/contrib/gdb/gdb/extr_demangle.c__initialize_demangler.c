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
struct cmd_list_element {int dummy; } ;
struct TYPE_2__ {scalar_t__ demangling_style; int /*<<< orphan*/  demangling_style_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_DEMANGLING_STYLE ; 
 struct cmd_list_element* add_set_enum_cmd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const**,char*,int /*<<< orphan*/ *) ; 
 struct cmd_list_element* add_show_from_set (struct cmd_list_element*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  class_support ; 
 int /*<<< orphan*/  current_demangling_style_string ; 
 int /*<<< orphan*/ * demangling_style_names ; 
 TYPE_1__* libiberty_demanglers ; 
 int /*<<< orphan*/  set_cmd_sfunc (struct cmd_list_element*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_demangling_command ; 
 int /*<<< orphan*/  set_demangling_style (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setlist ; 
 int /*<<< orphan*/  showlist ; 
 scalar_t__ unknown_demangling ; 
 int /*<<< orphan*/ * xcalloc (int,int) ; 
 int /*<<< orphan*/  xstrdup (int /*<<< orphan*/ ) ; 

void
_initialize_demangler (void)
{
  struct cmd_list_element *set, *show;
  int i, ndems;

  /* Fill the demangling_style_names[] array.  */
  for (ndems = 0;
       libiberty_demanglers[ndems].demangling_style != unknown_demangling; 
       ndems++)
    ;
  demangling_style_names = xcalloc (ndems + 1, sizeof (char *));
  for (i = 0;
       libiberty_demanglers[i].demangling_style != unknown_demangling; 
       i++)
    demangling_style_names[i] =
      xstrdup (libiberty_demanglers[i].demangling_style_name);

  set = add_set_enum_cmd ("demangle-style", class_support,
			  demangling_style_names,
			  (const char **) &current_demangling_style_string,
			  "Set the current C++ demangling style.\n\
Use `set demangle-style' without arguments for a list of demangling styles.",
			  &setlist);
  show = add_show_from_set (set, &showlist);
  set_cmd_sfunc (set, set_demangling_command);

  /* Set the default demangling style chosen at compilation time. */
  set_demangling_style (DEFAULT_DEMANGLING_STYLE);
}