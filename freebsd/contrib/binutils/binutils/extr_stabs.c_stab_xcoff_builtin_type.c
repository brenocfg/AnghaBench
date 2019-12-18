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
struct stab_handle {int /*<<< orphan*/ ** xcoff_types; } ;
typedef  int /*<<< orphan*/ * debug_type ;

/* Variables and functions */
 int /*<<< orphan*/ * DEBUG_TYPE_NULL ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int XCOFF_TYPE_COUNT ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/ * debug_make_bool_type (void*,int) ; 
 int /*<<< orphan*/ * debug_make_complex_type (void*,int) ; 
 int /*<<< orphan*/ * debug_make_float_type (void*,int) ; 
 int /*<<< orphan*/ * debug_make_int_type (void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * debug_make_void_type (void*) ; 
 int /*<<< orphan*/ * debug_name_type (void*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static debug_type
stab_xcoff_builtin_type (void *dhandle, struct stab_handle *info,
			 int typenum)
{
  debug_type rettype;
  const char *name;

  if (typenum >= 0 || typenum < -XCOFF_TYPE_COUNT)
    {
      fprintf (stderr, _("Unrecognized XCOFF type %d\n"), typenum);
      return DEBUG_TYPE_NULL;
    }
  if (info->xcoff_types[-typenum] != NULL)
    return info->xcoff_types[-typenum];

  switch (-typenum)
    {
    case 1:
      /* The size of this and all the other types are fixed, defined
	 by the debugging format.  */
      name = "int";
      rettype = debug_make_int_type (dhandle, 4, FALSE);
      break;
    case 2:
      name = "char";
      rettype = debug_make_int_type (dhandle, 1, FALSE);
      break;
    case 3:
      name = "short";
      rettype = debug_make_int_type (dhandle, 2, FALSE);
      break;
    case 4:
      name = "long";
      rettype = debug_make_int_type (dhandle, 4, FALSE);
      break;
    case 5:
      name = "unsigned char";
      rettype = debug_make_int_type (dhandle, 1, TRUE);
      break;
    case 6:
      name = "signed char";
      rettype = debug_make_int_type (dhandle, 1, FALSE);
      break;
    case 7:
      name = "unsigned short";
      rettype = debug_make_int_type (dhandle, 2, TRUE);
      break;
    case 8:
      name = "unsigned int";
      rettype = debug_make_int_type (dhandle, 4, TRUE);
      break;
    case 9:
      name = "unsigned";
      rettype = debug_make_int_type (dhandle, 4, TRUE);
    case 10:
      name = "unsigned long";
      rettype = debug_make_int_type (dhandle, 4, TRUE);
      break;
    case 11:
      name = "void";
      rettype = debug_make_void_type (dhandle);
      break;
    case 12:
      /* IEEE single precision (32 bit).  */
      name = "float";
      rettype = debug_make_float_type (dhandle, 4);
      break;
    case 13:
      /* IEEE double precision (64 bit).  */
      name = "double";
      rettype = debug_make_float_type (dhandle, 8);
      break;
    case 14:
      /* This is an IEEE double on the RS/6000, and different machines
	 with different sizes for "long double" should use different
	 negative type numbers.  See stabs.texinfo.  */
      name = "long double";
      rettype = debug_make_float_type (dhandle, 8);
      break;
    case 15:
      name = "integer";
      rettype = debug_make_int_type (dhandle, 4, FALSE);
      break;
    case 16:
      name = "boolean";
      rettype = debug_make_bool_type (dhandle, 4);
      break;
    case 17:
      name = "short real";
      rettype = debug_make_float_type (dhandle, 4);
      break;
    case 18:
      name = "real";
      rettype = debug_make_float_type (dhandle, 8);
      break;
    case 19:
      /* FIXME */
      name = "stringptr";
      rettype = NULL;
      break;
    case 20:
      /* FIXME */
      name = "character";
      rettype = debug_make_int_type (dhandle, 1, TRUE);
      break;
    case 21:
      name = "logical*1";
      rettype = debug_make_bool_type (dhandle, 1);
      break;
    case 22:
      name = "logical*2";
      rettype = debug_make_bool_type (dhandle, 2);
      break;
    case 23:
      name = "logical*4";
      rettype = debug_make_bool_type (dhandle, 4);
      break;
    case 24:
      name = "logical";
      rettype = debug_make_bool_type (dhandle, 4);
      break;
    case 25:
      /* Complex type consisting of two IEEE single precision values.  */
      name = "complex";
      rettype = debug_make_complex_type (dhandle, 8);
      break;
    case 26:
      /* Complex type consisting of two IEEE double precision values.  */
      name = "double complex";
      rettype = debug_make_complex_type (dhandle, 16);
      break;
    case 27:
      name = "integer*1";
      rettype = debug_make_int_type (dhandle, 1, FALSE);
      break;
    case 28:
      name = "integer*2";
      rettype = debug_make_int_type (dhandle, 2, FALSE);
      break;
    case 29:
      name = "integer*4";
      rettype = debug_make_int_type (dhandle, 4, FALSE);
      break;
    case 30:
      /* FIXME */
      name = "wchar";
      rettype = debug_make_int_type (dhandle, 2, FALSE);
      break;
    case 31:
      name = "long long";
      rettype = debug_make_int_type (dhandle, 8, FALSE);
      break;
    case 32:
      name = "unsigned long long";
      rettype = debug_make_int_type (dhandle, 8, TRUE);
      break;
    case 33:
      name = "logical*8";
      rettype = debug_make_bool_type (dhandle, 8);
      break;
    case 34:
      name = "integer*8";
      rettype = debug_make_int_type (dhandle, 8, FALSE);
      break;
    default:
      abort ();
    }

  rettype = debug_name_type (dhandle, name, rettype);

  info->xcoff_types[-typenum] = rettype;

  return rettype;
}