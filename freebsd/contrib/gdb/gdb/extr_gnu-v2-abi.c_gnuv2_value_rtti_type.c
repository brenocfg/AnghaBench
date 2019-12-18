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
struct value {int dummy; } ;
struct type {int dummy; } ;
struct symbol {int dummy; } ;
struct minimal_symbol {int dummy; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_TYPEDEF (struct type*) ; 
 char* DEPRECATED_SYMBOL_NAME (struct minimal_symbol*) ; 
 int DMGL_ANSI ; 
 int DMGL_PARAMS ; 
 int TYPE_BASECLASS_BITPOS (struct type*,scalar_t__) ; 
 scalar_t__ TYPE_CODE (struct type*) ; 
 scalar_t__ TYPE_CODE_CLASS ; 
 scalar_t__ TYPE_LENGTH (struct type*) ; 
 int TYPE_N_BASECLASSES (struct type*) ; 
 struct type* TYPE_VPTR_BASETYPE (struct type*) ; 
 scalar_t__ TYPE_VPTR_FIELDNO (struct type*) ; 
 scalar_t__ VALUE_ADDRESS (int /*<<< orphan*/ ) ; 
 struct type* VALUE_TYPE (struct value*) ; 
 struct type* cp_lookup_rtti_type (char*,int /*<<< orphan*/ *) ; 
 char* cplus_demangle (char*,int) ; 
 int /*<<< orphan*/  fill_in_vptr_fieldno (struct type*) ; 
 int /*<<< orphan*/  is_vtable_name (char*) ; 
 struct minimal_symbol* lookup_minimal_symbol_by_pc (int /*<<< orphan*/ ) ; 
 scalar_t__* strchr (char*,char) ; 
 int /*<<< orphan*/  value_as_address (int /*<<< orphan*/ ) ; 
 struct value* value_cast (struct type*,struct value*) ; 
 int /*<<< orphan*/  value_field (struct value*,scalar_t__) ; 

__attribute__((used)) static struct type *
gnuv2_value_rtti_type (struct value *v, int *full, int *top, int *using_enc)
{
  struct type *known_type;
  struct type *rtti_type;
  CORE_ADDR coreptr;
  struct value *vp;
  long top_offset = 0;
  char rtti_type_name[256];
  CORE_ADDR vtbl;
  struct minimal_symbol *minsym;
  struct symbol *sym;
  char *demangled_name;
  struct type *btype;

  if (full)
    *full = 0;
  if (top)
    *top = -1;
  if (using_enc)
    *using_enc = 0;

  /* Get declared type */
  known_type = VALUE_TYPE (v);
  CHECK_TYPEDEF (known_type);
  /* RTTI works only or class objects */
  if (TYPE_CODE (known_type) != TYPE_CODE_CLASS)
    return NULL;

  /* Plan on this changing in the future as i get around to setting
     the vtables properly for G++ compiled stuff.  Also, I'll be using
     the type info functions, which are always right.  Deal with it
     until then.  */

  /* If the type has no vptr fieldno, try to get it filled in */
  if (TYPE_VPTR_FIELDNO(known_type) < 0)
    fill_in_vptr_fieldno(known_type);

  /* If we still can't find one, give up */
  if (TYPE_VPTR_FIELDNO(known_type) < 0)
    return NULL;

  /* Make sure our basetype and known type match, otherwise, cast
     so we can get at the vtable properly.
  */
  btype = TYPE_VPTR_BASETYPE (known_type);
  CHECK_TYPEDEF (btype);
  if (btype != known_type )
    {
      v = value_cast (btype, v);
      if (using_enc)
        *using_enc=1;
    }
  /*
    We can't use value_ind here, because it would want to use RTTI, and
    we'd waste a bunch of time figuring out we already know the type.
    Besides, we don't care about the type, just the actual pointer
  */
  if (VALUE_ADDRESS (value_field (v, TYPE_VPTR_FIELDNO (known_type))) == 0)
    return NULL;

  vtbl=value_as_address(value_field(v,TYPE_VPTR_FIELDNO(known_type)));

  /* Try to find a symbol that is the vtable */
  minsym=lookup_minimal_symbol_by_pc(vtbl);
  if (minsym==NULL
      || (demangled_name=DEPRECATED_SYMBOL_NAME (minsym))==NULL
      || !is_vtable_name (demangled_name))
    return NULL;

  /* If we just skip the prefix, we get screwed by namespaces */
  demangled_name=cplus_demangle(demangled_name,DMGL_PARAMS|DMGL_ANSI);
  *(strchr(demangled_name,' '))=0;

  /* Lookup the type for the name */
  /* FIXME: chastain/2003-11-26: block=NULL is bogus.  See pr gdb/1465. */
  rtti_type = cp_lookup_rtti_type (demangled_name, NULL);
  if (rtti_type == NULL)
    return NULL;

  if (TYPE_N_BASECLASSES(rtti_type) > 1 &&  full && (*full) != 1)
    {
      if (top)
        *top=TYPE_BASECLASS_BITPOS(rtti_type,TYPE_VPTR_FIELDNO(rtti_type))/8;
      if (top && ((*top) >0))
        {
          if (TYPE_LENGTH(rtti_type) > TYPE_LENGTH(known_type))
            {
              if (full)
                *full=0;
            }
          else
            {
              if (full)
                *full=1;
            }
        }
    }
  else
    {
      if (full)
        *full=1;
    }

  return rtti_type;
}