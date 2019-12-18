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
struct demangle_component {int dummy; } ;
struct d_info {int expansion; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEMANGLE_COMPONENT_CONSTRUCTION_VTABLE ; 
 int /*<<< orphan*/  DEMANGLE_COMPONENT_COVARIANT_THUNK ; 
 int /*<<< orphan*/  DEMANGLE_COMPONENT_GUARD ; 
 int /*<<< orphan*/  DEMANGLE_COMPONENT_HIDDEN_ALIAS ; 
 int /*<<< orphan*/  DEMANGLE_COMPONENT_JAVA_CLASS ; 
 int /*<<< orphan*/  DEMANGLE_COMPONENT_REFTEMP ; 
 int /*<<< orphan*/  DEMANGLE_COMPONENT_THUNK ; 
 int /*<<< orphan*/  DEMANGLE_COMPONENT_TYPEINFO ; 
 int /*<<< orphan*/  DEMANGLE_COMPONENT_TYPEINFO_FN ; 
 int /*<<< orphan*/  DEMANGLE_COMPONENT_TYPEINFO_NAME ; 
 int /*<<< orphan*/  DEMANGLE_COMPONENT_VIRTUAL_THUNK ; 
 int /*<<< orphan*/  DEMANGLE_COMPONENT_VTABLE ; 
 int /*<<< orphan*/  DEMANGLE_COMPONENT_VTT ; 
 struct demangle_component* cplus_demangle_type (struct d_info*) ; 
 int /*<<< orphan*/  d_call_offset (struct d_info*,char) ; 
 scalar_t__ d_check_char (struct d_info*,char) ; 
 struct demangle_component* d_encoding (struct d_info*,int /*<<< orphan*/ ) ; 
 struct demangle_component* d_make_comp (struct d_info*,int /*<<< orphan*/ ,struct demangle_component*,struct demangle_component*) ; 
 struct demangle_component* d_name (struct d_info*) ; 
 int d_next_char (struct d_info*) ; 
 long d_number (struct d_info*) ; 

__attribute__((used)) static struct demangle_component *
d_special_name (struct d_info *di)
{
  di->expansion += 20;
  if (d_check_char (di, 'T'))
    {
      switch (d_next_char (di))
	{
	case 'V':
	  di->expansion -= 5;
	  return d_make_comp (di, DEMANGLE_COMPONENT_VTABLE,
			      cplus_demangle_type (di), NULL);
	case 'T':
	  di->expansion -= 10;
	  return d_make_comp (di, DEMANGLE_COMPONENT_VTT,
			      cplus_demangle_type (di), NULL);
	case 'I':
	  return d_make_comp (di, DEMANGLE_COMPONENT_TYPEINFO,
			      cplus_demangle_type (di), NULL);
	case 'S':
	  return d_make_comp (di, DEMANGLE_COMPONENT_TYPEINFO_NAME,
			      cplus_demangle_type (di), NULL);

	case 'h':
	  if (! d_call_offset (di, 'h'))
	    return NULL;
	  return d_make_comp (di, DEMANGLE_COMPONENT_THUNK,
			      d_encoding (di, 0), NULL);

	case 'v':
	  if (! d_call_offset (di, 'v'))
	    return NULL;
	  return d_make_comp (di, DEMANGLE_COMPONENT_VIRTUAL_THUNK,
			      d_encoding (di, 0), NULL);

	case 'c':
	  if (! d_call_offset (di, '\0'))
	    return NULL;
	  if (! d_call_offset (di, '\0'))
	    return NULL;
	  return d_make_comp (di, DEMANGLE_COMPONENT_COVARIANT_THUNK,
			      d_encoding (di, 0), NULL);

	case 'C':
	  {
	    struct demangle_component *derived_type;
	    long offset;
	    struct demangle_component *base_type;

	    derived_type = cplus_demangle_type (di);
	    offset = d_number (di);
	    if (offset < 0)
	      return NULL;
	    if (! d_check_char (di, '_'))
	      return NULL;
	    base_type = cplus_demangle_type (di);
	    /* We don't display the offset.  FIXME: We should display
	       it in verbose mode.  */
	    di->expansion += 5;
	    return d_make_comp (di, DEMANGLE_COMPONENT_CONSTRUCTION_VTABLE,
				base_type, derived_type);
	  }

	case 'F':
	  return d_make_comp (di, DEMANGLE_COMPONENT_TYPEINFO_FN,
			      cplus_demangle_type (di), NULL);
	case 'J':
	  return d_make_comp (di, DEMANGLE_COMPONENT_JAVA_CLASS,
			      cplus_demangle_type (di), NULL);

	default:
	  return NULL;
	}
    }
  else if (d_check_char (di, 'G'))
    {
      switch (d_next_char (di))
	{
	case 'V':
	  return d_make_comp (di, DEMANGLE_COMPONENT_GUARD, d_name (di), NULL);

	case 'R':
	  return d_make_comp (di, DEMANGLE_COMPONENT_REFTEMP, d_name (di),
			      NULL);

	case 'A':
	  return d_make_comp (di, DEMANGLE_COMPONENT_HIDDEN_ALIAS,
			      d_encoding (di, 0), NULL);

	default:
	  return NULL;
	}
    }
  else
    return NULL;
}