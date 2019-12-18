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
struct demangle_component {scalar_t__ type; } ;
struct d_print_template {int dummy; } ;
struct d_print_mod {int printed; struct d_print_mod* next; struct demangle_component* mod; struct d_print_template* templates; } ;
struct d_print_info {int options; struct d_print_template* templates; struct d_print_mod* modifiers; } ;

/* Variables and functions */
 scalar_t__ DEMANGLE_COMPONENT_ARRAY_TYPE ; 
 scalar_t__ DEMANGLE_COMPONENT_CONST_THIS ; 
 scalar_t__ DEMANGLE_COMPONENT_FUNCTION_TYPE ; 
 scalar_t__ DEMANGLE_COMPONENT_LOCAL_NAME ; 
 scalar_t__ DEMANGLE_COMPONENT_RESTRICT_THIS ; 
 scalar_t__ DEMANGLE_COMPONENT_VOLATILE_THIS ; 
 int DMGL_JAVA ; 
 int /*<<< orphan*/  d_append_char (struct d_print_info*,char) ; 
 int /*<<< orphan*/  d_append_string (struct d_print_info*,char*) ; 
 struct demangle_component* d_left (struct demangle_component*) ; 
 int /*<<< orphan*/  d_print_array_type (struct d_print_info*,struct demangle_component*,struct d_print_mod*) ; 
 int /*<<< orphan*/  d_print_comp (struct d_print_info*,struct demangle_component*) ; 
 int /*<<< orphan*/  d_print_function_type (struct d_print_info*,struct demangle_component*,struct d_print_mod*) ; 
 int /*<<< orphan*/  d_print_mod (struct d_print_info*,struct demangle_component*) ; 
 scalar_t__ d_print_saw_error (struct d_print_info*) ; 
 struct demangle_component* d_right (struct demangle_component*) ; 

__attribute__((used)) static void
d_print_mod_list (struct d_print_info *dpi,
                  struct d_print_mod *mods, int suffix)
{
  struct d_print_template *hold_dpt;

  if (mods == NULL || d_print_saw_error (dpi))
    return;

  if (mods->printed
      || (! suffix
	  && (mods->mod->type == DEMANGLE_COMPONENT_RESTRICT_THIS
	      || mods->mod->type == DEMANGLE_COMPONENT_VOLATILE_THIS
	      || mods->mod->type == DEMANGLE_COMPONENT_CONST_THIS)))
    {
      d_print_mod_list (dpi, mods->next, suffix);
      return;
    }

  mods->printed = 1;

  hold_dpt = dpi->templates;
  dpi->templates = mods->templates;

  if (mods->mod->type == DEMANGLE_COMPONENT_FUNCTION_TYPE)
    {
      d_print_function_type (dpi, mods->mod, mods->next);
      dpi->templates = hold_dpt;
      return;
    }
  else if (mods->mod->type == DEMANGLE_COMPONENT_ARRAY_TYPE)
    {
      d_print_array_type (dpi, mods->mod, mods->next);
      dpi->templates = hold_dpt;
      return;
    }
  else if (mods->mod->type == DEMANGLE_COMPONENT_LOCAL_NAME)
    {
      struct d_print_mod *hold_modifiers;
      struct demangle_component *dc;

      /* When this is on the modifier stack, we have pulled any
	 qualifiers off the right argument already.  Otherwise, we
	 print it as usual, but don't let the left argument see any
	 modifiers.  */

      hold_modifiers = dpi->modifiers;
      dpi->modifiers = NULL;
      d_print_comp (dpi, d_left (mods->mod));
      dpi->modifiers = hold_modifiers;

      if ((dpi->options & DMGL_JAVA) == 0)
	d_append_string (dpi, "::");
      else
	d_append_char (dpi, '.');

      dc = d_right (mods->mod);
      while (dc->type == DEMANGLE_COMPONENT_RESTRICT_THIS
	     || dc->type == DEMANGLE_COMPONENT_VOLATILE_THIS
	     || dc->type == DEMANGLE_COMPONENT_CONST_THIS)
	dc = d_left (dc);

      d_print_comp (dpi, dc);

      dpi->templates = hold_dpt;
      return;
    }

  d_print_mod (dpi, mods->mod);

  dpi->templates = hold_dpt;

  d_print_mod_list (dpi, mods->next, suffix);
}