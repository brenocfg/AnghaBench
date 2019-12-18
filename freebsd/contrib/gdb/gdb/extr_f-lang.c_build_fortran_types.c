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
struct objfile {int dummy; } ;
typedef  void* TYPE_TARGET_TYPE ;

/* Variables and functions */
 int TARGET_CHAR_BIT ; 
 int TARGET_DOUBLE_BIT ; 
 int TARGET_FLOAT_BIT ; 
 int TARGET_INT_BIT ; 
 int TARGET_LONG_DOUBLE_BIT ; 
 int TARGET_SHORT_BIT ; 
 int /*<<< orphan*/  TYPE_CODE_BOOL ; 
 int /*<<< orphan*/  TYPE_CODE_COMPLEX ; 
 int /*<<< orphan*/  TYPE_CODE_FLT ; 
 int /*<<< orphan*/  TYPE_CODE_INT ; 
 int /*<<< orphan*/  TYPE_CODE_VOID ; 
 int /*<<< orphan*/  TYPE_FLAG_UNSIGNED ; 
 void* builtin_type_f_character ; 
 void* builtin_type_f_complex_s16 ; 
 void* builtin_type_f_complex_s32 ; 
 void* builtin_type_f_complex_s8 ; 
 void* builtin_type_f_integer ; 
 void* builtin_type_f_integer_s2 ; 
 void* builtin_type_f_logical ; 
 void* builtin_type_f_logical_s1 ; 
 void* builtin_type_f_logical_s2 ; 
 void* builtin_type_f_real ; 
 void* builtin_type_f_real_s16 ; 
 void* builtin_type_f_real_s8 ; 
 void* builtin_type_f_void ; 
 void* init_type (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,struct objfile*) ; 

__attribute__((used)) static void
build_fortran_types (void)
{
  builtin_type_f_void =
    init_type (TYPE_CODE_VOID, 1,
	       0,
	       "VOID", (struct objfile *) NULL);

  builtin_type_f_character =
    init_type (TYPE_CODE_INT, TARGET_CHAR_BIT / TARGET_CHAR_BIT,
	       0,
	       "character", (struct objfile *) NULL);

  builtin_type_f_logical_s1 =
    init_type (TYPE_CODE_BOOL, TARGET_CHAR_BIT / TARGET_CHAR_BIT,
	       TYPE_FLAG_UNSIGNED,
	       "logical*1", (struct objfile *) NULL);

  builtin_type_f_integer_s2 =
    init_type (TYPE_CODE_INT, TARGET_SHORT_BIT / TARGET_CHAR_BIT,
	       0,
	       "integer*2", (struct objfile *) NULL);

  builtin_type_f_logical_s2 =
    init_type (TYPE_CODE_BOOL, TARGET_SHORT_BIT / TARGET_CHAR_BIT,
	       TYPE_FLAG_UNSIGNED,
	       "logical*2", (struct objfile *) NULL);

  builtin_type_f_integer =
    init_type (TYPE_CODE_INT, TARGET_INT_BIT / TARGET_CHAR_BIT,
	       0,
	       "integer", (struct objfile *) NULL);

  builtin_type_f_logical =
    init_type (TYPE_CODE_BOOL, TARGET_INT_BIT / TARGET_CHAR_BIT,
	       TYPE_FLAG_UNSIGNED,
	       "logical*4", (struct objfile *) NULL);

  builtin_type_f_real =
    init_type (TYPE_CODE_FLT, TARGET_FLOAT_BIT / TARGET_CHAR_BIT,
	       0,
	       "real", (struct objfile *) NULL);

  builtin_type_f_real_s8 =
    init_type (TYPE_CODE_FLT, TARGET_DOUBLE_BIT / TARGET_CHAR_BIT,
	       0,
	       "real*8", (struct objfile *) NULL);

  builtin_type_f_real_s16 =
    init_type (TYPE_CODE_FLT, TARGET_LONG_DOUBLE_BIT / TARGET_CHAR_BIT,
	       0,
	       "real*16", (struct objfile *) NULL);

  builtin_type_f_complex_s8 =
    init_type (TYPE_CODE_COMPLEX, 2 * TARGET_FLOAT_BIT / TARGET_CHAR_BIT,
	       0,
	       "complex*8", (struct objfile *) NULL);
  TYPE_TARGET_TYPE (builtin_type_f_complex_s8) = builtin_type_f_real;

  builtin_type_f_complex_s16 =
    init_type (TYPE_CODE_COMPLEX, 2 * TARGET_DOUBLE_BIT / TARGET_CHAR_BIT,
	       0,
	       "complex*16", (struct objfile *) NULL);
  TYPE_TARGET_TYPE (builtin_type_f_complex_s16) = builtin_type_f_real_s8;

  /* We have a new size == 4 double floats for the
     complex*32 data type */

  builtin_type_f_complex_s32 =
    init_type (TYPE_CODE_COMPLEX, 2 * TARGET_LONG_DOUBLE_BIT / TARGET_CHAR_BIT,
	       0,
	       "complex*32", (struct objfile *) NULL);
  TYPE_TARGET_TYPE (builtin_type_f_complex_s32) = builtin_type_f_real_s16;
}