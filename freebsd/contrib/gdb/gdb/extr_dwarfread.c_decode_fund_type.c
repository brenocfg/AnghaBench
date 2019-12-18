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

/* Variables and functions */
 int /*<<< orphan*/  DIE_ID ; 
 int /*<<< orphan*/  DIE_NAME ; 
 int /*<<< orphan*/  FT_BOOLEAN ; 
 int /*<<< orphan*/  FT_CHAR ; 
 int /*<<< orphan*/  FT_COMPLEX ; 
 int /*<<< orphan*/  FT_DBL_PREC_COMPLEX ; 
 int /*<<< orphan*/  FT_DBL_PREC_FLOAT ; 
 int /*<<< orphan*/  FT_EXT_PREC_COMPLEX ; 
 int /*<<< orphan*/  FT_EXT_PREC_FLOAT ; 
 int /*<<< orphan*/  FT_FLOAT ; 
 int /*<<< orphan*/  FT_INTEGER ; 
 int /*<<< orphan*/  FT_LONG ; 
 int /*<<< orphan*/  FT_LONG_LONG ; 
 int /*<<< orphan*/  FT_SHORT ; 
 int /*<<< orphan*/  FT_SIGNED_CHAR ; 
 int /*<<< orphan*/  FT_SIGNED_INTEGER ; 
 int /*<<< orphan*/  FT_SIGNED_LONG ; 
 int /*<<< orphan*/  FT_SIGNED_LONG_LONG ; 
 int /*<<< orphan*/  FT_SIGNED_SHORT ; 
 int /*<<< orphan*/  FT_UNSIGNED_CHAR ; 
 int /*<<< orphan*/  FT_UNSIGNED_INTEGER ; 
 int /*<<< orphan*/  FT_UNSIGNED_LONG ; 
 int /*<<< orphan*/  FT_UNSIGNED_LONG_LONG ; 
 int /*<<< orphan*/  FT_UNSIGNED_SHORT ; 
 int /*<<< orphan*/  FT_VOID ; 
#define  FT_boolean 151 
#define  FT_char 150 
#define  FT_complex 149 
#define  FT_dbl_prec_complex 148 
#define  FT_dbl_prec_float 147 
#define  FT_ext_prec_complex 146 
#define  FT_ext_prec_float 145 
#define  FT_float 144 
 unsigned int FT_hi_user ; 
#define  FT_integer 143 
 unsigned int FT_lo_user ; 
#define  FT_long 142 
#define  FT_long_long 141 
#define  FT_pointer 140 
#define  FT_short 139 
#define  FT_signed_char 138 
#define  FT_signed_integer 137 
#define  FT_signed_long 136 
#define  FT_signed_long_long 135 
#define  FT_signed_short 134 
#define  FT_unsigned_char 133 
#define  FT_unsigned_integer 132 
#define  FT_unsigned_long 131 
#define  FT_unsigned_long_long 130 
#define  FT_unsigned_short 129 
#define  FT_void 128 
 int /*<<< orphan*/  complaint (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  current_objfile ; 
 struct type* dwarf_fundamental_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct type* lookup_pointer_type (struct type*) ; 
 int /*<<< orphan*/  symfile_complaints ; 

__attribute__((used)) static struct type *
decode_fund_type (unsigned int fundtype)
{
  struct type *typep = NULL;

  switch (fundtype)
    {

    case FT_void:
      typep = dwarf_fundamental_type (current_objfile, FT_VOID);
      break;

    case FT_boolean:		/* Was FT_set in AT&T version */
      typep = dwarf_fundamental_type (current_objfile, FT_BOOLEAN);
      break;

    case FT_pointer:		/* (void *) */
      typep = dwarf_fundamental_type (current_objfile, FT_VOID);
      typep = lookup_pointer_type (typep);
      break;

    case FT_char:
      typep = dwarf_fundamental_type (current_objfile, FT_CHAR);
      break;

    case FT_signed_char:
      typep = dwarf_fundamental_type (current_objfile, FT_SIGNED_CHAR);
      break;

    case FT_unsigned_char:
      typep = dwarf_fundamental_type (current_objfile, FT_UNSIGNED_CHAR);
      break;

    case FT_short:
      typep = dwarf_fundamental_type (current_objfile, FT_SHORT);
      break;

    case FT_signed_short:
      typep = dwarf_fundamental_type (current_objfile, FT_SIGNED_SHORT);
      break;

    case FT_unsigned_short:
      typep = dwarf_fundamental_type (current_objfile, FT_UNSIGNED_SHORT);
      break;

    case FT_integer:
      typep = dwarf_fundamental_type (current_objfile, FT_INTEGER);
      break;

    case FT_signed_integer:
      typep = dwarf_fundamental_type (current_objfile, FT_SIGNED_INTEGER);
      break;

    case FT_unsigned_integer:
      typep = dwarf_fundamental_type (current_objfile, FT_UNSIGNED_INTEGER);
      break;

    case FT_long:
      typep = dwarf_fundamental_type (current_objfile, FT_LONG);
      break;

    case FT_signed_long:
      typep = dwarf_fundamental_type (current_objfile, FT_SIGNED_LONG);
      break;

    case FT_unsigned_long:
      typep = dwarf_fundamental_type (current_objfile, FT_UNSIGNED_LONG);
      break;

    case FT_long_long:
      typep = dwarf_fundamental_type (current_objfile, FT_LONG_LONG);
      break;

    case FT_signed_long_long:
      typep = dwarf_fundamental_type (current_objfile, FT_SIGNED_LONG_LONG);
      break;

    case FT_unsigned_long_long:
      typep = dwarf_fundamental_type (current_objfile, FT_UNSIGNED_LONG_LONG);
      break;

    case FT_float:
      typep = dwarf_fundamental_type (current_objfile, FT_FLOAT);
      break;

    case FT_dbl_prec_float:
      typep = dwarf_fundamental_type (current_objfile, FT_DBL_PREC_FLOAT);
      break;

    case FT_ext_prec_float:
      typep = dwarf_fundamental_type (current_objfile, FT_EXT_PREC_FLOAT);
      break;

    case FT_complex:
      typep = dwarf_fundamental_type (current_objfile, FT_COMPLEX);
      break;

    case FT_dbl_prec_complex:
      typep = dwarf_fundamental_type (current_objfile, FT_DBL_PREC_COMPLEX);
      break;

    case FT_ext_prec_complex:
      typep = dwarf_fundamental_type (current_objfile, FT_EXT_PREC_COMPLEX);
      break;

    }

  if (typep == NULL)
    {
      typep = dwarf_fundamental_type (current_objfile, FT_INTEGER);
      if (!(FT_lo_user <= fundtype && fundtype <= FT_hi_user))
	{
	  complaint (&symfile_complaints,
		     "DIE @ 0x%x \"%s\", unexpected fundamental type 0x%x",
		     DIE_ID, DIE_NAME, fundtype);
	}
    }

  return (typep);
}