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
struct ui_file {int dummy; } ;
struct type {int dummy; } ;
struct symbol {int dummy; } ;
struct fn_field {int dummy; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  DEPRECATED_SYMBOL_NAME (struct symbol*) ; 
 int DMGL_ANSI ; 
 int DMGL_PARAMS ; 
 scalar_t__ METHOD_PTR_IS_VIRTUAL (scalar_t__) ; 
 int METHOD_PTR_TO_VOFFSET (scalar_t__) ; 
 struct type* TYPE_DOMAIN_TYPE (struct type*) ; 
 struct fn_field* TYPE_FN_FIELDLIST1 (struct type*,unsigned int) ; 
 int TYPE_FN_FIELDLIST_LENGTH (struct type*,unsigned int) ; 
 int TYPE_FN_FIELD_PHYSNAME (struct fn_field*,int) ; 
 int TYPE_FN_FIELD_VOFFSET (struct fn_field*,int) ; 
 unsigned int TYPE_NFN_FIELDS (struct type*) ; 
 int /*<<< orphan*/  TYPE_TARGET_TYPE (struct type*) ; 
 int /*<<< orphan*/  check_stub_method_group (struct type*,unsigned int) ; 
 struct type* check_typedef (int /*<<< orphan*/ ) ; 
 char* cplus_demangle (int,int) ; 
 int /*<<< orphan*/  error (char*) ; 
 struct symbol* find_pc_function (scalar_t__) ; 
 int /*<<< orphan*/  fprintf_filtered (struct ui_file*,char*,...) ; 
 int /*<<< orphan*/  fputs_filtered (char*,struct ui_file*) ; 
 scalar_t__ hp_som_som_object_present ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  type_print (struct type*,char*,struct ui_file*,int) ; 
 scalar_t__ unpack_pointer (struct type*,char*) ; 
 int /*<<< orphan*/  xfree (char*) ; 

void
cp_print_class_method (char *valaddr,
		       struct type *type,
		       struct ui_file *stream)
{
  struct type *domain;
  struct fn_field *f = NULL;
  int j = 0;
  int len2;
  int offset;
  char *kind = "";
  CORE_ADDR addr;
  struct symbol *sym;
  unsigned len;
  unsigned int i;
  struct type *target_type = check_typedef (TYPE_TARGET_TYPE (type));

  domain = TYPE_DOMAIN_TYPE (target_type);
  if (domain == (struct type *) NULL)
    {
      fprintf_filtered (stream, "<unknown>");
      return;
    }
  addr = unpack_pointer (type, valaddr);
  if (METHOD_PTR_IS_VIRTUAL (addr))
    {
      offset = METHOD_PTR_TO_VOFFSET (addr);
      len = TYPE_NFN_FIELDS (domain);
      for (i = 0; i < len; i++)
	{
	  f = TYPE_FN_FIELDLIST1 (domain, i);
	  len2 = TYPE_FN_FIELDLIST_LENGTH (domain, i);

	  check_stub_method_group (domain, i);
	  for (j = 0; j < len2; j++)
	    {
	      if (TYPE_FN_FIELD_VOFFSET (f, j) == offset)
		{
		  kind = "virtual ";
		  goto common;
		}
	    }
	}
    }
  else
    {
      sym = find_pc_function (addr);
      if (sym == 0)
	{
	  /* 1997-08-01 Currently unsupported with HP aCC */
	  if (hp_som_som_object_present)
	    {
	      fputs_filtered ("?? <not supported with HP aCC>", stream);
	      return;
	    }
	  error ("invalid pointer to member function");
	}
      len = TYPE_NFN_FIELDS (domain);
      for (i = 0; i < len; i++)
	{
	  f = TYPE_FN_FIELDLIST1 (domain, i);
	  len2 = TYPE_FN_FIELDLIST_LENGTH (domain, i);

	  check_stub_method_group (domain, i);
	  for (j = 0; j < len2; j++)
	    {
	      if (strcmp (DEPRECATED_SYMBOL_NAME (sym), TYPE_FN_FIELD_PHYSNAME (f, j))
		  == 0)
		goto common;
	    }
	}
    }
 common:
  if (i < len)
    {
      char *demangled_name;

      fprintf_filtered (stream, "&");
      fputs_filtered (kind, stream);
      demangled_name = cplus_demangle (TYPE_FN_FIELD_PHYSNAME (f, j),
				       DMGL_ANSI | DMGL_PARAMS);
      if (demangled_name == NULL)
	fprintf_filtered (stream, "<badly mangled name %s>",
			  TYPE_FN_FIELD_PHYSNAME (f, j));
      else
	{
	  fputs_filtered (demangled_name, stream);
	  xfree (demangled_name);
	}
    }
  else
    {
      fprintf_filtered (stream, "(");
      type_print (type, "", stream, -1);
      fprintf_filtered (stream, ") %d", (int) addr >> 3);
    }
}