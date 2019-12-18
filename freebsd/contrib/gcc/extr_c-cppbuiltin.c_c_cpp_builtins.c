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
typedef  int /*<<< orphan*/  cpp_reader ;
struct TYPE_2__ {scalar_t__ handle_pragma_extern_prefix; scalar_t__ handle_pragma_redefine_extname; } ;

/* Variables and functions */
 int POINTER_SIZE ; 
 int /*<<< orphan*/  REGISTER_PREFIX ; 
 scalar_t__ SUPPORTS_ONE_ONLY ; 
 int /*<<< orphan*/  TARGET_CPU_CPP_BUILTINS () ; 
 scalar_t__ TARGET_DECLSPEC ; 
 int TARGET_DEC_EVAL_METHOD ; 
 int TARGET_FLT_EVAL_METHOD ; 
 int /*<<< orphan*/  TARGET_OBJFMT_CPP_BUILTINS () ; 
 int /*<<< orphan*/  TARGET_OS_CPP_BUILTINS () ; 
 int TYPE_PRECISION (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_UNSIGNED (int /*<<< orphan*/ ) ; 
 scalar_t__ USING_SJLJ_EXCEPTIONS ; 
 int /*<<< orphan*/  builtin_define (char*) ; 
 int /*<<< orphan*/  builtin_define_decimal_float_constants (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  builtin_define_float_constants (char*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  builtin_define_stdint_macros () ; 
 int /*<<< orphan*/  builtin_define_type_max (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  builtin_define_type_precision (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  builtin_define_with_int_value (char*,int) ; 
 int /*<<< orphan*/  builtin_define_with_value (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ c_dialect_cxx () ; 
 scalar_t__ c_dialect_objc () ; 
 int /*<<< orphan*/  c_stddef_cpp_builtins () ; 
 int /*<<< orphan*/  char_type_node ; 
 int /*<<< orphan*/  cpp_define (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  define__GNUC__ () ; 
 int /*<<< orphan*/  dfloat128_type_node ; 
 int /*<<< orphan*/  dfloat32_type_node ; 
 int /*<<< orphan*/  dfloat64_type_node ; 
 int /*<<< orphan*/  double_type_node ; 
 scalar_t__ fast_math_flags_set_p () ; 
 int flag_abi_version ; 
 scalar_t__ flag_blocks ; 
 scalar_t__ flag_exceptions ; 
 scalar_t__ flag_finite_math_only ; 
 scalar_t__ flag_gnu89_inline ; 
 scalar_t__ flag_iso ; 
 scalar_t__ flag_mudflap ; 
 scalar_t__ flag_next_runtime ; 
 scalar_t__ flag_openmp ; 
 int flag_pic ; 
 scalar_t__ flag_really_no_inline ; 
 scalar_t__ flag_signaling_nans ; 
 int /*<<< orphan*/  flag_signed_char ; 
 scalar_t__ flag_single_precision_constant ; 
 int flag_stack_protect ; 
 scalar_t__ flag_undef ; 
 scalar_t__ flag_weak ; 
 int /*<<< orphan*/  float_type_node ; 
 int /*<<< orphan*/  integer_type_node ; 
 int /*<<< orphan*/  long_double_type_node ; 
 int /*<<< orphan*/  long_integer_type_node ; 
 int /*<<< orphan*/  long_long_integer_type_node ; 
 scalar_t__ optimize ; 
 scalar_t__ optimize_size ; 
 int /*<<< orphan*/  short_integer_type_node ; 
 int /*<<< orphan*/  signed_char_type_node ; 
 TYPE_1__ targetm ; 
 int /*<<< orphan*/  user_label_prefix ; 
 int /*<<< orphan*/  version_string ; 
 scalar_t__ warn_deprecated ; 
 int /*<<< orphan*/  wchar_type_node ; 

void
c_cpp_builtins (cpp_reader *pfile)
{
  /* -undef turns off target-specific built-ins.  */
  if (flag_undef)
    return;

  define__GNUC__ ();

  /* For stddef.h.  They require macros defined in c-common.c.  */
  c_stddef_cpp_builtins ();

  if (c_dialect_cxx ())
    {
      if (flag_weak && SUPPORTS_ONE_ONLY)
	cpp_define (pfile, "__GXX_WEAK__=1");
      else
	cpp_define (pfile, "__GXX_WEAK__=0");
      if (warn_deprecated)
	cpp_define (pfile, "__DEPRECATED");
    }
  /* Note that we define this for C as well, so that we know if
     __attribute__((cleanup)) will interface with EH.  */
  if (flag_exceptions)
    cpp_define (pfile, "__EXCEPTIONS");

  /* Represents the C++ ABI version, always defined so it can be used while
     preprocessing C and assembler.  */
  if (flag_abi_version == 0)
    /* Use a very large value so that:

	 #if __GXX_ABI_VERSION >= <value for version X>

       will work whether the user explicitly says "-fabi-version=x" or
       "-fabi-version=0".  Do not use INT_MAX because that will be
       different from system to system.  */
    builtin_define_with_int_value ("__GXX_ABI_VERSION", 999999);
  else if (flag_abi_version == 1)
    /* Due to a historical accident, this version had the value
       "102".  */
    builtin_define_with_int_value ("__GXX_ABI_VERSION", 102);
  else
    /* Newer versions have values 1002, 1003, ....  */
    builtin_define_with_int_value ("__GXX_ABI_VERSION",
				   1000 + flag_abi_version);

  /* libgcc needs to know this.  */
  if (USING_SJLJ_EXCEPTIONS)
    cpp_define (pfile, "__USING_SJLJ_EXCEPTIONS__");

  /* limits.h needs to know these.  */
  builtin_define_type_max ("__SCHAR_MAX__", signed_char_type_node, 0);
  builtin_define_type_max ("__SHRT_MAX__", short_integer_type_node, 0);
  builtin_define_type_max ("__INT_MAX__", integer_type_node, 0);
  builtin_define_type_max ("__LONG_MAX__", long_integer_type_node, 1);
  builtin_define_type_max ("__LONG_LONG_MAX__", long_long_integer_type_node, 2);
  builtin_define_type_max ("__WCHAR_MAX__", wchar_type_node, 0);

  builtin_define_type_precision ("__CHAR_BIT__", char_type_node);

  /* stdint.h (eventually) and the testsuite need to know these.  */
  builtin_define_stdint_macros ();

  /* float.h needs to know these.  */

  builtin_define_with_int_value ("__FLT_EVAL_METHOD__",
				 TARGET_FLT_EVAL_METHOD);

  /* And decfloat.h needs this.  */
  builtin_define_with_int_value ("__DEC_EVAL_METHOD__",
                                 TARGET_DEC_EVAL_METHOD);

  builtin_define_float_constants ("FLT", "F", "%s", float_type_node);
  /* Cast the double precision constants when single precision constants are
     specified. The correct result is computed by the compiler when using 
     macros that include a cast. This has the side-effect of making the value 
     unusable in const expressions. */
  if (flag_single_precision_constant)
    builtin_define_float_constants ("DBL", "L", "((double)%s)", double_type_node);
  else
    builtin_define_float_constants ("DBL", "", "%s", double_type_node);
  builtin_define_float_constants ("LDBL", "L", "%s", long_double_type_node);

  /* For decfloat.h.  */
  builtin_define_decimal_float_constants ("DEC32", "DF", dfloat32_type_node);
  builtin_define_decimal_float_constants ("DEC64", "DD", dfloat64_type_node);
  builtin_define_decimal_float_constants ("DEC128", "DL", dfloat128_type_node);

  /* For use in assembly language.  */
  builtin_define_with_value ("__REGISTER_PREFIX__", REGISTER_PREFIX, 0);
  builtin_define_with_value ("__USER_LABEL_PREFIX__", user_label_prefix, 0);

  /* Misc.  */
  builtin_define_with_value ("__VERSION__", version_string, 1);

  if (flag_gnu89_inline)
    cpp_define (pfile, "__GNUC_GNU_INLINE__");
  else
    cpp_define (pfile, "__GNUC_STDC_INLINE__");

  /* Definitions for LP64 model.  */
  if (TYPE_PRECISION (long_integer_type_node) == 64
      && POINTER_SIZE == 64
      && TYPE_PRECISION (integer_type_node) == 32)
    {
      cpp_define (pfile, "_LP64");
      cpp_define (pfile, "__LP64__");
    }

  /* Other target-independent built-ins determined by command-line
     options.  */
  /* APPLE LOCAL begin blocks */
  /* APPLE LOCAL radar 5868913 */
  if (flag_blocks)
    {
      cpp_define (pfile, "__block=__attribute__((__blocks__(byref)))");
      cpp_define (pfile, "__BLOCKS__=1");
    }
  /* APPLE LOCAL end blocks */
  if (optimize_size)
    cpp_define (pfile, "__OPTIMIZE_SIZE__");
  if (optimize)
    cpp_define (pfile, "__OPTIMIZE__");

  if (fast_math_flags_set_p ())
    cpp_define (pfile, "__FAST_MATH__");
  if (flag_really_no_inline)
    cpp_define (pfile, "__NO_INLINE__");
  if (flag_signaling_nans)
    cpp_define (pfile, "__SUPPORT_SNAN__");
  if (flag_finite_math_only)
    cpp_define (pfile, "__FINITE_MATH_ONLY__=1");
  else
    cpp_define (pfile, "__FINITE_MATH_ONLY__=0");
  if (flag_pic)
    {
      builtin_define_with_int_value ("__pic__", flag_pic);
      builtin_define_with_int_value ("__PIC__", flag_pic);
    }

  if (flag_iso)
    cpp_define (pfile, "__STRICT_ANSI__");

  if (!flag_signed_char)
    cpp_define (pfile, "__CHAR_UNSIGNED__");

  if (c_dialect_cxx () && TYPE_UNSIGNED (wchar_type_node))
    cpp_define (pfile, "__WCHAR_UNSIGNED__");

  /* Make the choice of ObjC runtime visible to source code.  */
  if (c_dialect_objc () && flag_next_runtime)
    cpp_define (pfile, "__NEXT_RUNTIME__");

  /* Show the availability of some target pragmas.  */
  if (flag_mudflap || targetm.handle_pragma_redefine_extname)
    cpp_define (pfile, "__PRAGMA_REDEFINE_EXTNAME");

  if (targetm.handle_pragma_extern_prefix)
    cpp_define (pfile, "__PRAGMA_EXTERN_PREFIX");

  /* Make the choice of the stack protector runtime visible to source code.
     The macro names and values here were chosen for compatibility with an
     earlier implementation, i.e. ProPolice.  */
  if (flag_stack_protect == 3)
    cpp_define (pfile, "__SSP_STRONG__=3");
  else if (flag_stack_protect == 2)
    cpp_define (pfile, "__SSP_ALL__=2");
  else if (flag_stack_protect == 1)
    cpp_define (pfile, "__SSP__=1");

  if (flag_openmp)
    cpp_define (pfile, "_OPENMP=200505");

  /* A straightforward target hook doesn't work, because of problems
     linking that hook's body when part of non-C front ends.  */
# define preprocessing_asm_p() (cpp_get_options (pfile)->lang == CLK_ASM)
# define preprocessing_trad_p() (cpp_get_options (pfile)->traditional)
# define builtin_define(TXT) cpp_define (pfile, TXT)
# define builtin_assert(TXT) cpp_assert (pfile, TXT)
  TARGET_CPU_CPP_BUILTINS ();
  TARGET_OS_CPP_BUILTINS ();
  TARGET_OBJFMT_CPP_BUILTINS ();

  /* Support the __declspec keyword by turning them into attributes.
     Note that the current way we do this may result in a collision
     with predefined attributes later on.  This can be solved by using
     one attribute, say __declspec__, and passing args to it.  The
     problem with that approach is that args are not accumulated: each
     new appearance would clobber any existing args.  */
  if (TARGET_DECLSPEC)
    builtin_define ("__declspec(x)=__attribute__((x))");
}