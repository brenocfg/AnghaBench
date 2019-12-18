#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct demangle_component* right; } ;
struct TYPE_4__ {TYPE_1__ s_binary; } ;
struct demangle_component {scalar_t__ type; TYPE_2__ u; } ;
struct d_info {int options; } ;

/* Variables and functions */
 scalar_t__ DEMANGLE_COMPONENT_CONST_THIS ; 
 scalar_t__ DEMANGLE_COMPONENT_LOCAL_NAME ; 
 scalar_t__ DEMANGLE_COMPONENT_RESTRICT_THIS ; 
 int /*<<< orphan*/  DEMANGLE_COMPONENT_TYPED_NAME ; 
 scalar_t__ DEMANGLE_COMPONENT_VOLATILE_THIS ; 
 int DMGL_PARAMS ; 
 int /*<<< orphan*/  d_bare_function_type (struct d_info*,int /*<<< orphan*/ ) ; 
 struct demangle_component* d_left (struct demangle_component*) ; 
 struct demangle_component* d_make_comp (struct d_info*,int /*<<< orphan*/ ,struct demangle_component*,int /*<<< orphan*/ ) ; 
 struct demangle_component* d_name (struct d_info*) ; 
 char d_peek_char (struct d_info*) ; 
 struct demangle_component* d_right (struct demangle_component*) ; 
 struct demangle_component* d_special_name (struct d_info*) ; 
 int /*<<< orphan*/  has_return_type (struct demangle_component*) ; 

__attribute__((used)) static struct demangle_component *
d_encoding (struct d_info *di, int top_level)
{
  char peek = d_peek_char (di);

  if (peek == 'G' || peek == 'T')
    return d_special_name (di);
  else
    {
      struct demangle_component *dc;

      dc = d_name (di);

      if (dc != NULL && top_level && (di->options & DMGL_PARAMS) == 0)
	{
	  /* Strip off any initial CV-qualifiers, as they really apply
	     to the `this' parameter, and they were not output by the
	     v2 demangler without DMGL_PARAMS.  */
	  while (dc->type == DEMANGLE_COMPONENT_RESTRICT_THIS
		 || dc->type == DEMANGLE_COMPONENT_VOLATILE_THIS
		 || dc->type == DEMANGLE_COMPONENT_CONST_THIS)
	    dc = d_left (dc);

	  /* If the top level is a DEMANGLE_COMPONENT_LOCAL_NAME, then
	     there may be CV-qualifiers on its right argument which
	     really apply here; this happens when parsing a class
	     which is local to a function.  */
	  if (dc->type == DEMANGLE_COMPONENT_LOCAL_NAME)
	    {
	      struct demangle_component *dcr;

	      dcr = d_right (dc);
	      while (dcr->type == DEMANGLE_COMPONENT_RESTRICT_THIS
		     || dcr->type == DEMANGLE_COMPONENT_VOLATILE_THIS
		     || dcr->type == DEMANGLE_COMPONENT_CONST_THIS)
		dcr = d_left (dcr);
	      dc->u.s_binary.right = dcr;
	    }

	  return dc;
	}

      peek = d_peek_char (di);
      if (dc == NULL || peek == '\0' || peek == 'E')
	return dc;
      return d_make_comp (di, DEMANGLE_COMPONENT_TYPED_NAME, dc,
			  d_bare_function_type (di, has_return_type (dc)));
    }
}