#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int type; int bitlength; int /*<<< orphan*/  immediate; } ;
struct TYPE_5__ {TYPE_1__ dntti; } ;
typedef  TYPE_2__ dnttpointer ;

/* Variables and functions */
 int FT_BOOLEAN ; 
 int FT_CHAR ; 
 int FT_COMPLEX ; 
 int FT_DBL_PREC_COMPLEX ; 
 int FT_DBL_PREC_FLOAT ; 
 int FT_EXT_PREC_COMPLEX ; 
 int FT_EXT_PREC_FLOAT ; 
 int FT_FLOAT ; 
 int FT_INTEGER ; 
 int FT_LONG ; 
 int FT_LONG_LONG ; 
 int FT_SHORT ; 
 int FT_SIGNED_CHAR ; 
 int FT_STRING ; 
 int FT_TEMPLATE_ARG ; 
 int FT_UNSIGNED_CHAR ; 
 int FT_UNSIGNED_INTEGER ; 
 int FT_UNSIGNED_LONG ; 
 int FT_UNSIGNED_LONG_LONG ; 
 int FT_UNSIGNED_SHORT ; 
 int FT_VOID ; 
#define  HP_TYPE_ANYPOINTER 156 
#define  HP_TYPE_BOOLEAN 155 
#define  HP_TYPE_BOOLEAN_S300_COMPAT 154 
#define  HP_TYPE_BOOLEAN_VAX_COMPAT 153 
#define  HP_TYPE_CHAR 152 
#define  HP_TYPE_COMPLEX 151 
#define  HP_TYPE_COMPLEXS3000 150 
#define  HP_TYPE_DOUBLE 149 
#define  HP_TYPE_FLABEL 148 
#define  HP_TYPE_FTN_STRING_S300_COMPAT 147 
#define  HP_TYPE_FTN_STRING_SPEC 146 
#define  HP_TYPE_FTN_STRING_VAX_COMPAT 145 
#define  HP_TYPE_GLOBAL_ANYPOINTER 144 
#define  HP_TYPE_INT 143 
#define  HP_TYPE_LOCAL_ANYPOINTER 142 
#define  HP_TYPE_LONG 141 
#define  HP_TYPE_LONGSTRING200 140 
#define  HP_TYPE_MOD_STRING_3000 139 
#define  HP_TYPE_MOD_STRING_SPEC 138 
#define  HP_TYPE_PACKED_DECIMAL 137 
#define  HP_TYPE_REAL 136 
#define  HP_TYPE_REAL_3000 135 
#define  HP_TYPE_STRING200 134 
#define  HP_TYPE_TEMPLATE_ARG 133 
#define  HP_TYPE_TEXT 132 
#define  HP_TYPE_UNSIGNED_INT 131 
#define  HP_TYPE_UNSIGNED_LONG 130 
#define  HP_TYPE_VOID 129 
#define  HP_TYPE_WIDE_CHAR 128 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  warning (char*) ; 

__attribute__((used)) static int
hpread_type_translate (dnttpointer typep)
{
  if (!typep.dntti.immediate)
    {
      error ("error in hpread_type_translate\n.");
      return FT_VOID;
    }

  switch (typep.dntti.type)
    {
    case HP_TYPE_BOOLEAN:
    case HP_TYPE_BOOLEAN_S300_COMPAT:
    case HP_TYPE_BOOLEAN_VAX_COMPAT:
      return FT_BOOLEAN;
    case HP_TYPE_CHAR:		/* C signed char, C++ plain char */

    case HP_TYPE_WIDE_CHAR:
      return FT_CHAR;
    case HP_TYPE_INT:
      if (typep.dntti.bitlength <= 8)
	return FT_SIGNED_CHAR;	/* C++ signed char */
      if (typep.dntti.bitlength <= 16)
	return FT_SHORT;
      if (typep.dntti.bitlength <= 32)
	return FT_INTEGER;
      return FT_LONG_LONG;
    case HP_TYPE_LONG:
      if (typep.dntti.bitlength <= 8)
	return FT_SIGNED_CHAR;	/* C++ signed char. */
      return FT_LONG;
    case HP_TYPE_UNSIGNED_LONG:
      if (typep.dntti.bitlength <= 8)
	return FT_UNSIGNED_CHAR;	/* C/C++ unsigned char */
      if (typep.dntti.bitlength <= 16)
	return FT_UNSIGNED_SHORT;
      if (typep.dntti.bitlength <= 32)
	return FT_UNSIGNED_LONG;
      return FT_UNSIGNED_LONG_LONG;
    case HP_TYPE_UNSIGNED_INT:
      if (typep.dntti.bitlength <= 8)
	return FT_UNSIGNED_CHAR;
      if (typep.dntti.bitlength <= 16)
	return FT_UNSIGNED_SHORT;
      if (typep.dntti.bitlength <= 32)
	return FT_UNSIGNED_INTEGER;
      return FT_UNSIGNED_LONG_LONG;
    case HP_TYPE_REAL:
    case HP_TYPE_REAL_3000:
    case HP_TYPE_DOUBLE:
      if (typep.dntti.bitlength == 64)
	return FT_DBL_PREC_FLOAT;
      if (typep.dntti.bitlength == 128)
	return FT_EXT_PREC_FLOAT;
      return FT_FLOAT;
    case HP_TYPE_COMPLEX:
    case HP_TYPE_COMPLEXS3000:
      if (typep.dntti.bitlength == 128)
	return FT_DBL_PREC_COMPLEX;
      if (typep.dntti.bitlength == 192)
	return FT_EXT_PREC_COMPLEX;
      return FT_COMPLEX;
    case HP_TYPE_VOID:
      return FT_VOID;
    case HP_TYPE_STRING200:
    case HP_TYPE_LONGSTRING200:
    case HP_TYPE_FTN_STRING_SPEC:
    case HP_TYPE_MOD_STRING_SPEC:
    case HP_TYPE_MOD_STRING_3000:
    case HP_TYPE_FTN_STRING_S300_COMPAT:
    case HP_TYPE_FTN_STRING_VAX_COMPAT:
      return FT_STRING;
    case HP_TYPE_TEMPLATE_ARG:
      return FT_TEMPLATE_ARG;
    case HP_TYPE_TEXT:
    case HP_TYPE_FLABEL:
    case HP_TYPE_PACKED_DECIMAL:
    case HP_TYPE_ANYPOINTER:
    case HP_TYPE_GLOBAL_ANYPOINTER:
    case HP_TYPE_LOCAL_ANYPOINTER:
    default:
      warning ("hpread_type_translate: unhandled type code.\n");
      return FT_VOID;
    }
}