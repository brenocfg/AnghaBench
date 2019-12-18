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
typedef  union internal_auxent {int dummy; } internal_auxent ;
struct coff_types {int /*<<< orphan*/ * basic; } ;
struct coff_symbols {int dummy; } ;
typedef  int /*<<< orphan*/  debug_type ;
typedef  int /*<<< orphan*/  debug_field ;
typedef  int /*<<< orphan*/  bfd_signed_vma ;
typedef  scalar_t__ bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_TYPE_NULL ; 
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
#define  T_CHAR 143 
#define  T_DOUBLE 142 
#define  T_ENUM 141 
#define  T_FLOAT 140 
#define  T_INT 139 
#define  T_LNGDBL 138 
#define  T_LONG 137 
 int T_MAX ; 
#define  T_NULL 136 
#define  T_SHORT 135 
#define  T_STRUCT 134 
#define  T_UCHAR 133 
#define  T_UINT 132 
#define  T_ULONG 131 
#define  T_UNION 130 
#define  T_USHORT 129 
#define  T_VOID 128 
 int /*<<< orphan*/ * coff_get_slot (struct coff_types*,long) ; 
 int /*<<< orphan*/  debug_make_enum_type (void*,char const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debug_make_float_type (void*,int) ; 
 int /*<<< orphan*/  debug_make_int_type (void*,int,scalar_t__) ; 
 int /*<<< orphan*/  debug_make_struct_type (void*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debug_make_void_type (void*) ; 
 int /*<<< orphan*/  debug_name_type (void*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_coff_enum_type (int /*<<< orphan*/ *,struct coff_symbols*,struct coff_types*,union internal_auxent*,void*) ; 
 int /*<<< orphan*/  parse_coff_struct_type (int /*<<< orphan*/ *,struct coff_symbols*,struct coff_types*,int,union internal_auxent*,void*) ; 

__attribute__((used)) static debug_type
parse_coff_base_type (bfd *abfd, struct coff_symbols *symbols,
		      struct coff_types *types, long coff_symno, int ntype,
		      union internal_auxent *pauxent, void *dhandle)
{
  debug_type ret;
  bfd_boolean set_basic;
  const char *name;
  debug_type *slot;

  if (ntype >= 0
      && ntype <= T_MAX
      && types->basic[ntype] != DEBUG_TYPE_NULL)
    return types->basic[ntype];

  set_basic = TRUE;
  name = NULL;

  switch (ntype)
    {
    default:
      ret = debug_make_void_type (dhandle);
      break;

    case T_NULL:
    case T_VOID:
      ret = debug_make_void_type (dhandle);
      name = "void";
      break;

    case T_CHAR:
      ret = debug_make_int_type (dhandle, 1, FALSE);
      name = "char";
      break;

    case T_SHORT:
      ret = debug_make_int_type (dhandle, 2, FALSE);
      name = "short";
      break;

    case T_INT:
      /* FIXME: Perhaps the size should depend upon the architecture.  */
      ret = debug_make_int_type (dhandle, 4, FALSE);
      name = "int";
      break;

    case T_LONG:
      ret = debug_make_int_type (dhandle, 4, FALSE);
      name = "long";
      break;

    case T_FLOAT:
      ret = debug_make_float_type (dhandle, 4);
      name = "float";
      break;

    case T_DOUBLE:
      ret = debug_make_float_type (dhandle, 8);
      name = "double";
      break;

    case T_LNGDBL:
      ret = debug_make_float_type (dhandle, 12);
      name = "long double";
      break;

    case T_UCHAR:
      ret = debug_make_int_type (dhandle, 1, TRUE);
      name = "unsigned char";
      break;

    case T_USHORT:
      ret = debug_make_int_type (dhandle, 2, TRUE);
      name = "unsigned short";
      break;

    case T_UINT:
      ret = debug_make_int_type (dhandle, 4, TRUE);
      name = "unsigned int";
      break;

    case T_ULONG:
      ret = debug_make_int_type (dhandle, 4, TRUE);
      name = "unsigned long";
      break;

    case T_STRUCT:
      if (pauxent == NULL)
	ret = debug_make_struct_type (dhandle, TRUE, 0,
				      (debug_field *) NULL);
      else
	ret = parse_coff_struct_type (abfd, symbols, types, ntype, pauxent,
				      dhandle);

      slot = coff_get_slot (types, coff_symno);
      *slot = ret;

      set_basic = FALSE;
      break;

    case T_UNION:
      if (pauxent == NULL)
	ret = debug_make_struct_type (dhandle, FALSE, 0, (debug_field *) NULL);
      else
	ret = parse_coff_struct_type (abfd, symbols, types, ntype, pauxent,
				      dhandle);

      slot = coff_get_slot (types, coff_symno);
      *slot = ret;

      set_basic = FALSE;
      break;

    case T_ENUM:
      if (pauxent == NULL)
	ret = debug_make_enum_type (dhandle, (const char **) NULL,
				    (bfd_signed_vma *) NULL);
      else
	ret = parse_coff_enum_type (abfd, symbols, types, pauxent, dhandle);

      slot = coff_get_slot (types, coff_symno);
      *slot = ret;

      set_basic = FALSE;
      break;
    }

  if (name != NULL)
    ret = debug_name_type (dhandle, name, ret);

  if (set_basic
      && ntype >= 0
      && ntype <= T_MAX)
    types->basic[ntype] = ret;

  return ret;
}