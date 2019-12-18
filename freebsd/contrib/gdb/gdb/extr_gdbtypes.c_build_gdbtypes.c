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
typedef  void* TYPE_FLOATFORMAT ;

/* Variables and functions */
 int TARGET_ADDR_BIT ; 
 int TARGET_BFD_VMA_BIT ; 
 int TARGET_CHAR_BIT ; 
 scalar_t__ TARGET_CHAR_SIGNED ; 
 int TARGET_DOUBLE_BIT ; 
 void* TARGET_DOUBLE_FORMAT ; 
 int TARGET_FLOAT_BIT ; 
 void* TARGET_FLOAT_FORMAT ; 
 int TARGET_INT_BIT ; 
 int TARGET_LONG_BIT ; 
 int TARGET_LONG_DOUBLE_BIT ; 
 void* TARGET_LONG_DOUBLE_FORMAT ; 
 int TARGET_LONG_LONG_BIT ; 
 int TARGET_SHORT_BIT ; 
 int /*<<< orphan*/  TYPE_CODE_BOOL ; 
 int /*<<< orphan*/  TYPE_CODE_CHAR ; 
 int /*<<< orphan*/  TYPE_CODE_COMPLEX ; 
 int /*<<< orphan*/  TYPE_CODE_FLT ; 
 int /*<<< orphan*/  TYPE_CODE_INT ; 
 int /*<<< orphan*/  TYPE_CODE_STRING ; 
 int /*<<< orphan*/  TYPE_CODE_VOID ; 
 int TYPE_FLAG_NOSIGN ; 
 int TYPE_FLAG_UNSIGNED ; 
 int /*<<< orphan*/  add_set_cmd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_show_from_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  build_builtin_type_vec128 () ; 
 int /*<<< orphan*/  build_builtin_type_vec128i () ; 
 int /*<<< orphan*/  build_builtin_type_vec64 () ; 
 int /*<<< orphan*/  build_builtin_type_vec64i () ; 
 void* builtin_type_CORE_ADDR ; 
 void* builtin_type_bfd_vma ; 
 void* builtin_type_bool ; 
 void* builtin_type_char ; 
 void* builtin_type_complex ; 
 void* builtin_type_double ; 
 void* builtin_type_double_complex ; 
 void* builtin_type_float ; 
 void* builtin_type_int ; 
 void* builtin_type_int0 ; 
 void* builtin_type_int128 ; 
 void* builtin_type_int16 ; 
 void* builtin_type_int32 ; 
 void* builtin_type_int64 ; 
 void* builtin_type_int8 ; 
 void* builtin_type_long ; 
 void* builtin_type_long_double ; 
 void* builtin_type_long_long ; 
 void* builtin_type_short ; 
 void* builtin_type_signed_char ; 
 void* builtin_type_string ; 
 void* builtin_type_true_char ; 
 void* builtin_type_uint128 ; 
 void* builtin_type_uint16 ; 
 void* builtin_type_uint32 ; 
 void* builtin_type_uint64 ; 
 void* builtin_type_uint8 ; 
 void* builtin_type_unsigned_char ; 
 void* builtin_type_unsigned_int ; 
 void* builtin_type_unsigned_long ; 
 void* builtin_type_unsigned_long_long ; 
 void* builtin_type_unsigned_short ; 
 void* builtin_type_v16_int8 ; 
 void* builtin_type_v16qi ; 
 void* builtin_type_v2_double ; 
 void* builtin_type_v2_float ; 
 void* builtin_type_v2_int32 ; 
 void* builtin_type_v2_int64 ; 
 void* builtin_type_v2si ; 
 void* builtin_type_v4_float ; 
 void* builtin_type_v4_int16 ; 
 void* builtin_type_v4_int32 ; 
 void* builtin_type_v4hi ; 
 void* builtin_type_v4sf ; 
 void* builtin_type_v4si ; 
 void* builtin_type_v8_int16 ; 
 void* builtin_type_v8_int8 ; 
 void* builtin_type_v8hi ; 
 void* builtin_type_v8qi ; 
 int /*<<< orphan*/  builtin_type_vec128 ; 
 int /*<<< orphan*/  builtin_type_vec128i ; 
 int /*<<< orphan*/  builtin_type_vec64 ; 
 int /*<<< orphan*/  builtin_type_vec64i ; 
 void* builtin_type_void ; 
 int /*<<< orphan*/  builtin_type_void_data_ptr ; 
 int /*<<< orphan*/  builtin_type_void_func_ptr ; 
 int /*<<< orphan*/  class_support ; 
 void* init_simd_type (char*,void*,char*,int) ; 
 void* init_type (int /*<<< orphan*/ ,int,int,char*,struct objfile*) ; 
 void* init_vector_type (void*,int) ; 
 int /*<<< orphan*/  lookup_function_type (void*) ; 
 int /*<<< orphan*/  lookup_pointer_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_pointer_type (void*,int /*<<< orphan*/ *) ; 
 int opaque_type_resolution ; 
 int /*<<< orphan*/  setlist ; 
 int /*<<< orphan*/  showlist ; 
 int /*<<< orphan*/  var_boolean ; 

__attribute__((used)) static void
build_gdbtypes (void)
{
  builtin_type_void =
    init_type (TYPE_CODE_VOID, 1,
	       0,
	       "void", (struct objfile *) NULL);
  builtin_type_char =
    init_type (TYPE_CODE_INT, TARGET_CHAR_BIT / TARGET_CHAR_BIT,
	       (TYPE_FLAG_NOSIGN
                | (TARGET_CHAR_SIGNED ? 0 : TYPE_FLAG_UNSIGNED)),
	       "char", (struct objfile *) NULL);
  builtin_type_true_char =
    init_type (TYPE_CODE_CHAR, TARGET_CHAR_BIT / TARGET_CHAR_BIT,
	       0,
	       "true character", (struct objfile *) NULL);
  builtin_type_signed_char =
    init_type (TYPE_CODE_INT, TARGET_CHAR_BIT / TARGET_CHAR_BIT,
	       0,
	       "signed char", (struct objfile *) NULL);
  builtin_type_unsigned_char =
    init_type (TYPE_CODE_INT, TARGET_CHAR_BIT / TARGET_CHAR_BIT,
	       TYPE_FLAG_UNSIGNED,
	       "unsigned char", (struct objfile *) NULL);
  builtin_type_short =
    init_type (TYPE_CODE_INT, TARGET_SHORT_BIT / TARGET_CHAR_BIT,
	       0,
	       "short", (struct objfile *) NULL);
  builtin_type_unsigned_short =
    init_type (TYPE_CODE_INT, TARGET_SHORT_BIT / TARGET_CHAR_BIT,
	       TYPE_FLAG_UNSIGNED,
	       "unsigned short", (struct objfile *) NULL);
  builtin_type_int =
    init_type (TYPE_CODE_INT, TARGET_INT_BIT / TARGET_CHAR_BIT,
	       0,
	       "int", (struct objfile *) NULL);
  builtin_type_unsigned_int =
    init_type (TYPE_CODE_INT, TARGET_INT_BIT / TARGET_CHAR_BIT,
	       TYPE_FLAG_UNSIGNED,
	       "unsigned int", (struct objfile *) NULL);
  builtin_type_long =
    init_type (TYPE_CODE_INT, TARGET_LONG_BIT / TARGET_CHAR_BIT,
	       0,
	       "long", (struct objfile *) NULL);
  builtin_type_unsigned_long =
    init_type (TYPE_CODE_INT, TARGET_LONG_BIT / TARGET_CHAR_BIT,
	       TYPE_FLAG_UNSIGNED,
	       "unsigned long", (struct objfile *) NULL);
  builtin_type_long_long =
    init_type (TYPE_CODE_INT, TARGET_LONG_LONG_BIT / TARGET_CHAR_BIT,
	       0,
	       "long long", (struct objfile *) NULL);
  builtin_type_unsigned_long_long =
    init_type (TYPE_CODE_INT, TARGET_LONG_LONG_BIT / TARGET_CHAR_BIT,
	       TYPE_FLAG_UNSIGNED,
	       "unsigned long long", (struct objfile *) NULL);
  builtin_type_float =
    init_type (TYPE_CODE_FLT, TARGET_FLOAT_BIT / TARGET_CHAR_BIT,
	       0,
	       "float", (struct objfile *) NULL);
/* vinschen@redhat.com 2002-02-08:
   The below lines are disabled since they are doing the wrong
   thing for non-multiarch targets.  They are setting the correct
   type of floats for the target but while on multiarch targets
   this is done everytime the architecture changes, it's done on
   non-multiarch targets only on startup, leaving the wrong values
   in even if the architecture changes (eg. from big-endian to
   little-endian).  */
#if 0
  TYPE_FLOATFORMAT (builtin_type_float) = TARGET_FLOAT_FORMAT;
#endif
  builtin_type_double =
    init_type (TYPE_CODE_FLT, TARGET_DOUBLE_BIT / TARGET_CHAR_BIT,
	       0,
	       "double", (struct objfile *) NULL);
#if 0
  TYPE_FLOATFORMAT (builtin_type_double) = TARGET_DOUBLE_FORMAT;
#endif
  builtin_type_long_double =
    init_type (TYPE_CODE_FLT, TARGET_LONG_DOUBLE_BIT / TARGET_CHAR_BIT,
	       0,
	       "long double", (struct objfile *) NULL);
#if 0
  TYPE_FLOATFORMAT (builtin_type_long_double) = TARGET_LONG_DOUBLE_FORMAT;
#endif
  builtin_type_complex =
    init_type (TYPE_CODE_COMPLEX, 2 * TARGET_FLOAT_BIT / TARGET_CHAR_BIT,
	       0,
	       "complex", (struct objfile *) NULL);
  TYPE_TARGET_TYPE (builtin_type_complex) = builtin_type_float;
  builtin_type_double_complex =
    init_type (TYPE_CODE_COMPLEX, 2 * TARGET_DOUBLE_BIT / TARGET_CHAR_BIT,
	       0,
	       "double complex", (struct objfile *) NULL);
  TYPE_TARGET_TYPE (builtin_type_double_complex) = builtin_type_double;
  builtin_type_string =
    init_type (TYPE_CODE_STRING, TARGET_CHAR_BIT / TARGET_CHAR_BIT,
	       0,
	       "string", (struct objfile *) NULL);
  builtin_type_int0 =
    init_type (TYPE_CODE_INT, 0 / 8,
	       0,
	       "int0_t", (struct objfile *) NULL);
  builtin_type_int8 =
    init_type (TYPE_CODE_INT, 8 / 8,
	       0,
	       "int8_t", (struct objfile *) NULL);
  builtin_type_uint8 =
    init_type (TYPE_CODE_INT, 8 / 8,
	       TYPE_FLAG_UNSIGNED,
	       "uint8_t", (struct objfile *) NULL);
  builtin_type_int16 =
    init_type (TYPE_CODE_INT, 16 / 8,
	       0,
	       "int16_t", (struct objfile *) NULL);
  builtin_type_uint16 =
    init_type (TYPE_CODE_INT, 16 / 8,
	       TYPE_FLAG_UNSIGNED,
	       "uint16_t", (struct objfile *) NULL);
  builtin_type_int32 =
    init_type (TYPE_CODE_INT, 32 / 8,
	       0,
	       "int32_t", (struct objfile *) NULL);
  builtin_type_uint32 =
    init_type (TYPE_CODE_INT, 32 / 8,
	       TYPE_FLAG_UNSIGNED,
	       "uint32_t", (struct objfile *) NULL);
  builtin_type_int64 =
    init_type (TYPE_CODE_INT, 64 / 8,
	       0,
	       "int64_t", (struct objfile *) NULL);
  builtin_type_uint64 =
    init_type (TYPE_CODE_INT, 64 / 8,
	       TYPE_FLAG_UNSIGNED,
	       "uint64_t", (struct objfile *) NULL);
  builtin_type_int128 =
    init_type (TYPE_CODE_INT, 128 / 8,
	       0,
	       "int128_t", (struct objfile *) NULL);
  builtin_type_uint128 =
    init_type (TYPE_CODE_INT, 128 / 8,
	       TYPE_FLAG_UNSIGNED,
	       "uint128_t", (struct objfile *) NULL);
  builtin_type_bool =
    init_type (TYPE_CODE_BOOL, TARGET_CHAR_BIT / TARGET_CHAR_BIT,
	       0,
	       "bool", (struct objfile *) NULL);

  /* Add user knob for controlling resolution of opaque types */
  add_show_from_set
    (add_set_cmd ("opaque-type-resolution", class_support, var_boolean, (char *) &opaque_type_resolution,
		  "Set resolution of opaque struct/class/union types (if set before loading symbols).",
		  &setlist),
     &showlist);
  opaque_type_resolution = 1;

  /* Build SIMD types.  */
  builtin_type_v4sf
    = init_simd_type ("__builtin_v4sf", builtin_type_float, "f", 4);
  builtin_type_v4si
    = init_simd_type ("__builtin_v4si", builtin_type_int32, "f", 4);
  builtin_type_v16qi
    = init_simd_type ("__builtin_v16qi", builtin_type_int8, "f", 16);
  builtin_type_v8qi
    = init_simd_type ("__builtin_v8qi", builtin_type_int8, "f", 8);
  builtin_type_v8hi
    = init_simd_type ("__builtin_v8hi", builtin_type_int16, "f", 8);
  builtin_type_v4hi
    = init_simd_type ("__builtin_v4hi", builtin_type_int16, "f", 4);
  builtin_type_v2si
    = init_simd_type ("__builtin_v2si", builtin_type_int32, "f", 2);

  /* 128 bit vectors.  */
  builtin_type_v2_double = init_vector_type (builtin_type_double, 2);
  builtin_type_v4_float = init_vector_type (builtin_type_float, 4);
  builtin_type_v2_int64 = init_vector_type (builtin_type_int64, 2);
  builtin_type_v4_int32 = init_vector_type (builtin_type_int32, 4);
  builtin_type_v8_int16 = init_vector_type (builtin_type_int16, 8);
  builtin_type_v16_int8 = init_vector_type (builtin_type_int8, 16);
  /* 64 bit vectors.  */
  builtin_type_v2_float = init_vector_type (builtin_type_float, 2);
  builtin_type_v2_int32 = init_vector_type (builtin_type_int32, 2);
  builtin_type_v4_int16 = init_vector_type (builtin_type_int16, 4);
  builtin_type_v8_int8 = init_vector_type (builtin_type_int8, 8);

  /* Vector types.  */
  builtin_type_vec64 = build_builtin_type_vec64 ();
  builtin_type_vec64i = build_builtin_type_vec64i ();
  builtin_type_vec128 = build_builtin_type_vec128 ();
  builtin_type_vec128i = build_builtin_type_vec128i ();

  /* Pointer/Address types. */

  /* NOTE: on some targets, addresses and pointers are not necessarily
     the same --- for example, on the D10V, pointers are 16 bits long,
     but addresses are 32 bits long.  See doc/gdbint.texinfo,
     ``Pointers Are Not Always Addresses''.

     The upshot is:
     - gdb's `struct type' always describes the target's
       representation.
     - gdb's `struct value' objects should always hold values in
       target form.
     - gdb's CORE_ADDR values are addresses in the unified virtual
       address space that the assembler and linker work with.  Thus,
       since target_read_memory takes a CORE_ADDR as an argument, it
       can access any memory on the target, even if the processor has
       separate code and data address spaces.

     So, for example:
     - If v is a value holding a D10V code pointer, its contents are
       in target form: a big-endian address left-shifted two bits.
     - If p is a D10V pointer type, TYPE_LENGTH (p) == 2, just as
       sizeof (void *) == 2 on the target.

     In this context, builtin_type_CORE_ADDR is a bit odd: it's a
     target type for a value the target will never see.  It's only
     used to hold the values of (typeless) linker symbols, which are
     indeed in the unified virtual address space.  */
  builtin_type_void_data_ptr = make_pointer_type (builtin_type_void, NULL);
  builtin_type_void_func_ptr
    = lookup_pointer_type (lookup_function_type (builtin_type_void));
  builtin_type_CORE_ADDR =
    init_type (TYPE_CODE_INT, TARGET_ADDR_BIT / 8,
	       TYPE_FLAG_UNSIGNED,
	       "__CORE_ADDR", (struct objfile *) NULL);
  builtin_type_bfd_vma =
    init_type (TYPE_CODE_INT, TARGET_BFD_VMA_BIT / 8,
	       TYPE_FLAG_UNSIGNED,
	       "__bfd_vma", (struct objfile *) NULL);
}