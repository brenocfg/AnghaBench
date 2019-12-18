#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* type; } ;
struct TYPE_6__ {TYPE_2__ s_builtin; } ;
struct demangle_component {scalar_t__ type; TYPE_3__ u; } ;
struct d_info {int /*<<< orphan*/  expansion; } ;
typedef  enum demangle_component_type { ____Placeholder_demangle_component_type } demangle_component_type ;
struct TYPE_4__ {scalar_t__ print; scalar_t__ len; } ;

/* Variables and functions */
 scalar_t__ DEMANGLE_COMPONENT_BUILTIN_TYPE ; 
 int DEMANGLE_COMPONENT_LITERAL ; 
 int DEMANGLE_COMPONENT_LITERAL_NEG ; 
 scalar_t__ D_PRINT_DEFAULT ; 
 struct demangle_component* cplus_demangle_mangled_name (struct d_info*,int /*<<< orphan*/ ) ; 
 struct demangle_component* cplus_demangle_type (struct d_info*) ; 
 int /*<<< orphan*/  d_advance (struct d_info*,int) ; 
 int /*<<< orphan*/  d_check_char (struct d_info*,char) ; 
 struct demangle_component* d_make_comp (struct d_info*,int,struct demangle_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_make_name (struct d_info*,char const*,int) ; 
 char d_peek_char (struct d_info*) ; 
 char const* d_str (struct d_info*) ; 

__attribute__((used)) static struct demangle_component *
d_expr_primary (struct d_info *di)
{
  struct demangle_component *ret;

  if (! d_check_char (di, 'L'))
    return NULL;
  if (d_peek_char (di) == '_')
    ret = cplus_demangle_mangled_name (di, 0);
  else
    {
      struct demangle_component *type;
      enum demangle_component_type t;
      const char *s;

      type = cplus_demangle_type (di);
      if (type == NULL)
	return NULL;

      /* If we have a type we know how to print, we aren't going to
	 print the type name itself.  */
      if (type->type == DEMANGLE_COMPONENT_BUILTIN_TYPE
	  && type->u.s_builtin.type->print != D_PRINT_DEFAULT)
	di->expansion -= type->u.s_builtin.type->len;

      /* Rather than try to interpret the literal value, we just
	 collect it as a string.  Note that it's possible to have a
	 floating point literal here.  The ABI specifies that the
	 format of such literals is machine independent.  That's fine,
	 but what's not fine is that versions of g++ up to 3.2 with
	 -fabi-version=1 used upper case letters in the hex constant,
	 and dumped out gcc's internal representation.  That makes it
	 hard to tell where the constant ends, and hard to dump the
	 constant in any readable form anyhow.  We don't attempt to
	 handle these cases.  */

      t = DEMANGLE_COMPONENT_LITERAL;
      if (d_peek_char (di) == 'n')
	{
	  t = DEMANGLE_COMPONENT_LITERAL_NEG;
	  d_advance (di, 1);
	}
      s = d_str (di);
      while (d_peek_char (di) != 'E')
	{
	  if (d_peek_char (di) == '\0')
	    return NULL;
	  d_advance (di, 1);
	}
      ret = d_make_comp (di, t, type, d_make_name (di, s, d_str (di) - s));
    }
  if (! d_check_char (di, 'E'))
    return NULL;
  return ret;
}