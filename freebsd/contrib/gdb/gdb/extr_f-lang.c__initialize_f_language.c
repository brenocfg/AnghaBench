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

/* Variables and functions */
 int /*<<< orphan*/  DEPRECATED_REGISTER_GDBARCH_SWAP (int /*<<< orphan*/ ) ; 
 int TARGET_CHAR_BIT ; 
 int /*<<< orphan*/  TYPE_CODE_STRING ; 
 int /*<<< orphan*/  add_language (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  build_fortran_types () ; 
 int /*<<< orphan*/  builtin_type_f_character ; 
 int /*<<< orphan*/  builtin_type_f_complex_s16 ; 
 int /*<<< orphan*/  builtin_type_f_complex_s32 ; 
 int /*<<< orphan*/  builtin_type_f_complex_s8 ; 
 int /*<<< orphan*/  builtin_type_f_integer ; 
 int /*<<< orphan*/  builtin_type_f_integer_s2 ; 
 int /*<<< orphan*/  builtin_type_f_logical ; 
 int /*<<< orphan*/  builtin_type_f_logical_s1 ; 
 int /*<<< orphan*/  builtin_type_f_logical_s2 ; 
 int /*<<< orphan*/  builtin_type_f_real ; 
 int /*<<< orphan*/  builtin_type_f_real_s16 ; 
 int /*<<< orphan*/  builtin_type_f_real_s8 ; 
 int /*<<< orphan*/  builtin_type_f_void ; 
 int /*<<< orphan*/  builtin_type_string ; 
 int /*<<< orphan*/  deprecated_register_gdbarch_swap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  (*) ()) ; 
 int /*<<< orphan*/  f_language_defn ; 
 int /*<<< orphan*/  init_type (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,struct objfile*) ; 

void
_initialize_f_language (void)
{
  build_fortran_types ();

  DEPRECATED_REGISTER_GDBARCH_SWAP (builtin_type_f_character);
  DEPRECATED_REGISTER_GDBARCH_SWAP (builtin_type_f_logical); 
  DEPRECATED_REGISTER_GDBARCH_SWAP (builtin_type_f_logical_s1); 
  DEPRECATED_REGISTER_GDBARCH_SWAP (builtin_type_f_logical_s2); 
  DEPRECATED_REGISTER_GDBARCH_SWAP (builtin_type_f_integer); 
  DEPRECATED_REGISTER_GDBARCH_SWAP (builtin_type_f_integer_s2); 
  DEPRECATED_REGISTER_GDBARCH_SWAP (builtin_type_f_real); 
  DEPRECATED_REGISTER_GDBARCH_SWAP (builtin_type_f_real_s8); 
  DEPRECATED_REGISTER_GDBARCH_SWAP (builtin_type_f_real_s16); 
  DEPRECATED_REGISTER_GDBARCH_SWAP (builtin_type_f_complex_s8); 
  DEPRECATED_REGISTER_GDBARCH_SWAP (builtin_type_f_complex_s16); 
  DEPRECATED_REGISTER_GDBARCH_SWAP (builtin_type_f_complex_s32); 
  DEPRECATED_REGISTER_GDBARCH_SWAP (builtin_type_f_void); 
  DEPRECATED_REGISTER_GDBARCH_SWAP (builtin_type_string); 
  deprecated_register_gdbarch_swap (NULL, 0, build_fortran_types);

  builtin_type_string =
    init_type (TYPE_CODE_STRING, TARGET_CHAR_BIT / TARGET_CHAR_BIT,
	       0,
	       "character string", (struct objfile *) NULL);

  add_language (&f_language_defn);
}