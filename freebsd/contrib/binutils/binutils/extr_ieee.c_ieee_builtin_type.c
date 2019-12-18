#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ ** builtins; } ;
struct ieee_info {TYPE_1__ types; void* dhandle; } ;
typedef  enum builtin_types { ____Placeholder_builtin_types } builtin_types ;
typedef  int /*<<< orphan*/ * debug_type ;
typedef  int /*<<< orphan*/  bfd_byte ;

/* Variables and functions */
 unsigned int BUILTIN_TYPE_COUNT ; 
 int /*<<< orphan*/ * DEBUG_TYPE_NULL ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  assert (int) ; 
#define  builtin_bcd_float 153 
#define  builtin_char 152 
#define  builtin_double 151 
#define  builtin_float 150 
#define  builtin_instruction_address 149 
#define  builtin_int 148 
#define  builtin_long 147 
#define  builtin_long_double 146 
#define  builtin_long_long_double 145 
#define  builtin_quoted_string 144 
#define  builtin_short 143 
#define  builtin_short_int 142 
#define  builtin_signed_char 141 
#define  builtin_signed_long 140 
#define  builtin_signed_long_long 139 
#define  builtin_signed_short 138 
#define  builtin_signed_short_int 137 
#define  builtin_unknown 136 
#define  builtin_unsigned 135 
#define  builtin_unsigned_char 134 
#define  builtin_unsigned_int 133 
#define  builtin_unsigned_long 132 
#define  builtin_unsigned_long_long 131 
#define  builtin_unsigned_short 130 
#define  builtin_unsigned_short_int 129 
#define  builtin_void 128 
 int /*<<< orphan*/ * debug_make_array_type (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * debug_make_float_type (void*,int) ; 
 int /*<<< orphan*/ * debug_make_int_type (void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * debug_make_pointer_type (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * debug_make_void_type (void*) ; 
 int /*<<< orphan*/ * debug_name_type (void*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee_error (struct ieee_info*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static debug_type
ieee_builtin_type (struct ieee_info *info, const bfd_byte *p,
		   unsigned int indx)
{
  void *dhandle;
  debug_type type;
  const char *name;

  if (indx < BUILTIN_TYPE_COUNT
      && info->types.builtins[indx] != DEBUG_TYPE_NULL)
    return info->types.builtins[indx];

  dhandle = info->dhandle;

  if (indx >= 32 && indx < 64)
    {
      type = debug_make_pointer_type (dhandle,
				      ieee_builtin_type (info, p, indx - 32));
      assert (indx < BUILTIN_TYPE_COUNT);
      info->types.builtins[indx] = type;
      return type;
    }

  switch ((enum builtin_types) indx)
    {
    default:
      ieee_error (info, p, _("unknown builtin type"));
      return NULL;

    case builtin_unknown:
      type = debug_make_void_type (dhandle);
      name = NULL;
      break;

    case builtin_void:
      type = debug_make_void_type (dhandle);
      name = "void";
      break;

    case builtin_signed_char:
      type = debug_make_int_type (dhandle, 1, FALSE);
      name = "signed char";
      break;

    case builtin_unsigned_char:
      type = debug_make_int_type (dhandle, 1, TRUE);
      name = "unsigned char";
      break;

    case builtin_signed_short_int:
      type = debug_make_int_type (dhandle, 2, FALSE);
      name = "signed short int";
      break;

    case builtin_unsigned_short_int:
      type = debug_make_int_type (dhandle, 2, TRUE);
      name = "unsigned short int";
      break;

    case builtin_signed_long:
      type = debug_make_int_type (dhandle, 4, FALSE);
      name = "signed long";
      break;

    case builtin_unsigned_long:
      type = debug_make_int_type (dhandle, 4, TRUE);
      name = "unsigned long";
      break;

    case builtin_signed_long_long:
      type = debug_make_int_type (dhandle, 8, FALSE);
      name = "signed long long";
      break;

    case builtin_unsigned_long_long:
      type = debug_make_int_type (dhandle, 8, TRUE);
      name = "unsigned long long";
      break;

    case builtin_float:
      type = debug_make_float_type (dhandle, 4);
      name = "float";
      break;

    case builtin_double:
      type = debug_make_float_type (dhandle, 8);
      name = "double";
      break;

    case builtin_long_double:
      /* FIXME: The size for this type should depend upon the
         processor.  */
      type = debug_make_float_type (dhandle, 12);
      name = "long double";
      break;

    case builtin_long_long_double:
      type = debug_make_float_type (dhandle, 16);
      name = "long long double";
      break;

    case builtin_quoted_string:
      type = debug_make_array_type (dhandle,
				    ieee_builtin_type (info, p,
						       ((unsigned int)
							builtin_char)),
				    ieee_builtin_type (info, p,
						       ((unsigned int)
							builtin_int)),
				    0, -1, TRUE);
      name = "QUOTED STRING";
      break;

    case builtin_instruction_address:
      /* FIXME: This should be a code address.  */
      type = debug_make_int_type (dhandle, 4, TRUE);
      name = "instruction address";
      break;

    case builtin_int:
      /* FIXME: The size for this type should depend upon the
         processor.  */
      type = debug_make_int_type (dhandle, 4, FALSE);
      name = "int";
      break;

    case builtin_unsigned:
      /* FIXME: The size for this type should depend upon the
         processor.  */
      type = debug_make_int_type (dhandle, 4, TRUE);
      name = "unsigned";
      break;

    case builtin_unsigned_int:
      /* FIXME: The size for this type should depend upon the
         processor.  */
      type = debug_make_int_type (dhandle, 4, TRUE);
      name = "unsigned int";
      break;

    case builtin_char:
      type = debug_make_int_type (dhandle, 1, FALSE);
      name = "char";
      break;

    case builtin_long:
      type = debug_make_int_type (dhandle, 4, FALSE);
      name = "long";
      break;

    case builtin_short:
      type = debug_make_int_type (dhandle, 2, FALSE);
      name = "short";
      break;

    case builtin_unsigned_short:
      type = debug_make_int_type (dhandle, 2, TRUE);
      name = "unsigned short";
      break;

    case builtin_short_int:
      type = debug_make_int_type (dhandle, 2, FALSE);
      name = "short int";
      break;

    case builtin_signed_short:
      type = debug_make_int_type (dhandle, 2, FALSE);
      name = "signed short";
      break;

    case builtin_bcd_float:
      ieee_error (info, p, _("BCD float type not supported"));
      return DEBUG_TYPE_NULL;
    }

  if (name != NULL)
    type = debug_name_type (dhandle, name, type);

  assert (indx < BUILTIN_TYPE_COUNT);

  info->types.builtins[indx] = type;

  return type;
}