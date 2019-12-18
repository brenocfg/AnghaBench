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
struct demangle_component {int type; } ;
struct d_print_info {int options; } ;

/* Variables and functions */
#define  DEMANGLE_COMPONENT_COMPLEX 140 
#define  DEMANGLE_COMPONENT_CONST 139 
#define  DEMANGLE_COMPONENT_CONST_THIS 138 
#define  DEMANGLE_COMPONENT_IMAGINARY 137 
#define  DEMANGLE_COMPONENT_POINTER 136 
#define  DEMANGLE_COMPONENT_PTRMEM_TYPE 135 
#define  DEMANGLE_COMPONENT_REFERENCE 134 
#define  DEMANGLE_COMPONENT_RESTRICT 133 
#define  DEMANGLE_COMPONENT_RESTRICT_THIS 132 
#define  DEMANGLE_COMPONENT_TYPED_NAME 131 
#define  DEMANGLE_COMPONENT_VENDOR_TYPE_QUAL 130 
#define  DEMANGLE_COMPONENT_VOLATILE 129 
#define  DEMANGLE_COMPONENT_VOLATILE_THIS 128 
 int DMGL_JAVA ; 
 int /*<<< orphan*/  d_append_char (struct d_print_info*,char) ; 
 int /*<<< orphan*/  d_append_string_constant (struct d_print_info*,char*) ; 
 char d_last_char (struct d_print_info*) ; 
 struct demangle_component const* d_left (struct demangle_component const*) ; 
 int /*<<< orphan*/  d_print_comp (struct d_print_info*,struct demangle_component const*) ; 
 struct demangle_component const* d_right (struct demangle_component const*) ; 

__attribute__((used)) static void
d_print_mod (struct d_print_info *dpi,
             const struct demangle_component *mod)
{
  switch (mod->type)
    {
    case DEMANGLE_COMPONENT_RESTRICT:
    case DEMANGLE_COMPONENT_RESTRICT_THIS:
      d_append_string_constant (dpi, " restrict");
      return;
    case DEMANGLE_COMPONENT_VOLATILE:
    case DEMANGLE_COMPONENT_VOLATILE_THIS:
      d_append_string_constant (dpi, " volatile");
      return;
    case DEMANGLE_COMPONENT_CONST:
    case DEMANGLE_COMPONENT_CONST_THIS:
      d_append_string_constant (dpi, " const");
      return;
    case DEMANGLE_COMPONENT_VENDOR_TYPE_QUAL:
      d_append_char (dpi, ' ');
      d_print_comp (dpi, d_right (mod));
      return;
    case DEMANGLE_COMPONENT_POINTER:
      /* There is no pointer symbol in Java.  */
      if ((dpi->options & DMGL_JAVA) == 0)
	d_append_char (dpi, '*');
      return;
    case DEMANGLE_COMPONENT_REFERENCE:
      d_append_char (dpi, '&');
      return;
    case DEMANGLE_COMPONENT_COMPLEX:
      d_append_string_constant (dpi, "complex ");
      return;
    case DEMANGLE_COMPONENT_IMAGINARY:
      d_append_string_constant (dpi, "imaginary ");
      return;
    case DEMANGLE_COMPONENT_PTRMEM_TYPE:
      if (d_last_char (dpi) != '(')
	d_append_char (dpi, ' ');
      d_print_comp (dpi, d_left (mod));
      d_append_string_constant (dpi, "::*");
      return;
    case DEMANGLE_COMPONENT_TYPED_NAME:
      d_print_comp (dpi, d_left (mod));
      return;
    default:
      /* Otherwise, we have something that won't go back on the
	 modifier stack, so we can just print it.  */
      d_print_comp (dpi, mod);
      return;
    }
}