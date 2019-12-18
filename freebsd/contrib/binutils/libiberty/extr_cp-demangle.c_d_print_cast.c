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
struct d_print_template {struct d_print_template* next; struct demangle_component const* template_decl; } ;
struct d_print_mod {int dummy; } ;
struct d_print_info {struct d_print_mod* modifiers; struct d_print_template* templates; } ;

/* Variables and functions */
 scalar_t__ DEMANGLE_COMPONENT_TEMPLATE ; 
 int /*<<< orphan*/  d_append_char (struct d_print_info*,char) ; 
 char d_last_char (struct d_print_info*) ; 
 struct demangle_component const* d_left (struct demangle_component const*) ; 
 int /*<<< orphan*/  d_print_comp (struct d_print_info*,struct demangle_component const*) ; 
 struct demangle_component const* d_right (struct demangle_component const*) ; 

__attribute__((used)) static void
d_print_cast (struct d_print_info *dpi,
              const struct demangle_component *dc)
{
  if (d_left (dc)->type != DEMANGLE_COMPONENT_TEMPLATE)
    d_print_comp (dpi, d_left (dc));
  else
    {
      struct d_print_mod *hold_dpm;
      struct d_print_template dpt;

      /* It appears that for a templated cast operator, we need to put
	 the template parameters in scope for the operator name, but
	 not for the parameters.  The effect is that we need to handle
	 the template printing here.  */

      hold_dpm = dpi->modifiers;
      dpi->modifiers = NULL;

      dpt.next = dpi->templates;
      dpi->templates = &dpt;
      dpt.template_decl = d_left (dc);

      d_print_comp (dpi, d_left (d_left (dc)));

      dpi->templates = dpt.next;

      if (d_last_char (dpi) == '<')
	d_append_char (dpi, ' ');
      d_append_char (dpi, '<');
      d_print_comp (dpi, d_right (d_left (dc)));
      /* Avoid generating two consecutive '>' characters, to avoid
	 the C++ syntactic ambiguity.  */
      if (d_last_char (dpi) == '>')
	d_append_char (dpi, ' ');
      d_append_char (dpi, '>');

      dpi->modifiers = hold_dpm;
    }
}