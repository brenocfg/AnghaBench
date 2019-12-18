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
struct type {int dummy; } ;
struct objfile {int dummy; } ;
struct dwarf2_cu {struct objfile* objfile; } ;

/* Variables and functions */
#define  DW_ATE_address 135 
#define  DW_ATE_boolean 134 
#define  DW_ATE_complex_float 133 
#define  DW_ATE_float 132 
#define  DW_ATE_signed 131 
#define  DW_ATE_signed_char 130 
#define  DW_ATE_unsigned 129 
#define  DW_ATE_unsigned_char 128 
 int /*<<< orphan*/  FT_BOOLEAN ; 
 int /*<<< orphan*/  FT_COMPLEX ; 
 int /*<<< orphan*/  FT_DBL_PREC_COMPLEX ; 
 int /*<<< orphan*/  FT_DBL_PREC_FLOAT ; 
 int /*<<< orphan*/  FT_FLOAT ; 
 int /*<<< orphan*/  FT_SIGNED_CHAR ; 
 int /*<<< orphan*/  FT_SIGNED_INTEGER ; 
 int /*<<< orphan*/  FT_SIGNED_SHORT ; 
 int /*<<< orphan*/  FT_UNSIGNED_CHAR ; 
 int /*<<< orphan*/  FT_UNSIGNED_INTEGER ; 
 int /*<<< orphan*/  FT_UNSIGNED_SHORT ; 
 int /*<<< orphan*/  FT_VOID ; 
 struct type* dwarf2_fundamental_type (struct objfile*,int /*<<< orphan*/ ,struct dwarf2_cu*) ; 

__attribute__((used)) static struct type *
dwarf_base_type (int encoding, int size, struct dwarf2_cu *cu)
{
  struct objfile *objfile = cu->objfile;

  /* FIXME - this should not produce a new (struct type *)
     every time.  It should cache base types.  */
  struct type *type;
  switch (encoding)
    {
    case DW_ATE_address:
      type = dwarf2_fundamental_type (objfile, FT_VOID, cu);
      return type;
    case DW_ATE_boolean:
      type = dwarf2_fundamental_type (objfile, FT_BOOLEAN, cu);
      return type;
    case DW_ATE_complex_float:
      if (size == 16)
	{
	  type = dwarf2_fundamental_type (objfile, FT_DBL_PREC_COMPLEX, cu);
	}
      else
	{
	  type = dwarf2_fundamental_type (objfile, FT_COMPLEX, cu);
	}
      return type;
    case DW_ATE_float:
      if (size == 8)
	{
	  type = dwarf2_fundamental_type (objfile, FT_DBL_PREC_FLOAT, cu);
	}
      else
	{
	  type = dwarf2_fundamental_type (objfile, FT_FLOAT, cu);
	}
      return type;
    case DW_ATE_signed:
      switch (size)
	{
	case 1:
	  type = dwarf2_fundamental_type (objfile, FT_SIGNED_CHAR, cu);
	  break;
	case 2:
	  type = dwarf2_fundamental_type (objfile, FT_SIGNED_SHORT, cu);
	  break;
	default:
	case 4:
	  type = dwarf2_fundamental_type (objfile, FT_SIGNED_INTEGER, cu);
	  break;
	}
      return type;
    case DW_ATE_signed_char:
      type = dwarf2_fundamental_type (objfile, FT_SIGNED_CHAR, cu);
      return type;
    case DW_ATE_unsigned:
      switch (size)
	{
	case 1:
	  type = dwarf2_fundamental_type (objfile, FT_UNSIGNED_CHAR, cu);
	  break;
	case 2:
	  type = dwarf2_fundamental_type (objfile, FT_UNSIGNED_SHORT, cu);
	  break;
	default:
	case 4:
	  type = dwarf2_fundamental_type (objfile, FT_UNSIGNED_INTEGER, cu);
	  break;
	}
      return type;
    case DW_ATE_unsigned_char:
      type = dwarf2_fundamental_type (objfile, FT_UNSIGNED_CHAR, cu);
      return type;
    default:
      type = dwarf2_fundamental_type (objfile, FT_SIGNED_INTEGER, cu);
      return type;
    }
}