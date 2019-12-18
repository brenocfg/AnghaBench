#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_1__ ;

/* Type definitions */
struct cmd_list_element {int dummy; } ;
typedef  TYPE_1__* TYPE_FLOATFORMAT ;
struct TYPE_34__ {int totalsize; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEPRECATED_REGISTER_GDBARCH_SWAP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_CODE_FLT ; 
 int /*<<< orphan*/  add_set_cmd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_show_from_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  build_gdbtypes () ; 
 int /*<<< orphan*/  builtin_type_CORE_ADDR ; 
 TYPE_1__* builtin_type_arm_ext_big ; 
 TYPE_1__* builtin_type_arm_ext_littlebyte_bigword ; 
 int /*<<< orphan*/  builtin_type_bfd_vma ; 
 int /*<<< orphan*/  builtin_type_char ; 
 int /*<<< orphan*/  builtin_type_complex ; 
 int /*<<< orphan*/  builtin_type_double ; 
 int /*<<< orphan*/  builtin_type_double_complex ; 
 int /*<<< orphan*/  builtin_type_float ; 
 TYPE_1__* builtin_type_i387_ext ; 
 TYPE_1__* builtin_type_i960_ext ; 
 TYPE_1__* builtin_type_ia64_quad_big ; 
 TYPE_1__* builtin_type_ia64_quad_little ; 
 TYPE_1__* builtin_type_ia64_spill_big ; 
 TYPE_1__* builtin_type_ia64_spill_little ; 
 TYPE_1__* builtin_type_ieee_double_big ; 
 TYPE_1__* builtin_type_ieee_double_little ; 
 TYPE_1__* builtin_type_ieee_double_littlebyte_bigword ; 
 TYPE_1__* builtin_type_ieee_single_big ; 
 TYPE_1__* builtin_type_ieee_single_little ; 
 int /*<<< orphan*/  builtin_type_int ; 
 int /*<<< orphan*/  builtin_type_int128 ; 
 int /*<<< orphan*/  builtin_type_int16 ; 
 int /*<<< orphan*/  builtin_type_int32 ; 
 int /*<<< orphan*/  builtin_type_int64 ; 
 int /*<<< orphan*/  builtin_type_int8 ; 
 int /*<<< orphan*/  builtin_type_long ; 
 int /*<<< orphan*/  builtin_type_long_double ; 
 int /*<<< orphan*/  builtin_type_long_long ; 
 TYPE_1__* builtin_type_m68881_ext ; 
 TYPE_1__* builtin_type_m88110_ext ; 
 TYPE_1__* builtin_type_m88110_harris_ext ; 
 int /*<<< orphan*/  builtin_type_short ; 
 int /*<<< orphan*/  builtin_type_signed_char ; 
 int /*<<< orphan*/  builtin_type_string ; 
 int /*<<< orphan*/  builtin_type_uint128 ; 
 int /*<<< orphan*/  builtin_type_uint16 ; 
 int /*<<< orphan*/  builtin_type_uint32 ; 
 int /*<<< orphan*/  builtin_type_uint64 ; 
 int /*<<< orphan*/  builtin_type_uint8 ; 
 int /*<<< orphan*/  builtin_type_unsigned_char ; 
 int /*<<< orphan*/  builtin_type_unsigned_int ; 
 int /*<<< orphan*/  builtin_type_unsigned_long ; 
 int /*<<< orphan*/  builtin_type_unsigned_long_long ; 
 int /*<<< orphan*/  builtin_type_unsigned_short ; 
 int /*<<< orphan*/  builtin_type_v16_int8 ; 
 int /*<<< orphan*/  builtin_type_v16qi ; 
 int /*<<< orphan*/  builtin_type_v2_double ; 
 int /*<<< orphan*/  builtin_type_v2_float ; 
 int /*<<< orphan*/  builtin_type_v2_int32 ; 
 int /*<<< orphan*/  builtin_type_v2_int64 ; 
 int /*<<< orphan*/  builtin_type_v2si ; 
 int /*<<< orphan*/  builtin_type_v4_float ; 
 int /*<<< orphan*/  builtin_type_v4_int16 ; 
 int /*<<< orphan*/  builtin_type_v4_int32 ; 
 int /*<<< orphan*/  builtin_type_v4hi ; 
 int /*<<< orphan*/  builtin_type_v4sf ; 
 int /*<<< orphan*/  builtin_type_v4si ; 
 int /*<<< orphan*/  builtin_type_v8_int16 ; 
 int /*<<< orphan*/  builtin_type_v8_int8 ; 
 int /*<<< orphan*/  builtin_type_v8hi ; 
 int /*<<< orphan*/  builtin_type_v8qi ; 
 int /*<<< orphan*/  builtin_type_vec128 ; 
 int /*<<< orphan*/  builtin_type_vec128i ; 
 int /*<<< orphan*/  builtin_type_void ; 
 int /*<<< orphan*/  builtin_type_void_data_ptr ; 
 int /*<<< orphan*/  builtin_type_void_func_ptr ; 
 int /*<<< orphan*/  deprecated_register_gdbarch_swap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  (*) ()) ; 
 TYPE_1__ floatformat_arm_ext_big ; 
 TYPE_1__ floatformat_arm_ext_littlebyte_bigword ; 
 TYPE_1__ floatformat_i387_ext ; 
 TYPE_1__ floatformat_i960_ext ; 
 TYPE_1__ floatformat_ia64_quad_big ; 
 TYPE_1__ floatformat_ia64_quad_little ; 
 TYPE_1__ floatformat_ia64_spill_big ; 
 TYPE_1__ floatformat_ia64_spill_little ; 
 TYPE_1__ floatformat_ieee_double_big ; 
 TYPE_1__ floatformat_ieee_double_little ; 
 TYPE_1__ floatformat_ieee_double_littlebyte_bigword ; 
 TYPE_1__ floatformat_ieee_single_big ; 
 TYPE_1__ floatformat_ieee_single_little ; 
 TYPE_1__ floatformat_m68881_ext ; 
 TYPE_1__ floatformat_m88110_ext ; 
 TYPE_1__ floatformat_m88110_harris_ext ; 
 void* init_type (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  no_class ; 
 int /*<<< orphan*/  overload_debug ; 
 int /*<<< orphan*/  setdebuglist ; 
 int /*<<< orphan*/  showdebuglist ; 
 int /*<<< orphan*/  var_zinteger ; 

void
_initialize_gdbtypes (void)
{
  struct cmd_list_element *c;
  build_gdbtypes ();

  /* FIXME - For the moment, handle types by swapping them in and out.
     Should be using the per-architecture data-pointer and a large
     struct. */
  DEPRECATED_REGISTER_GDBARCH_SWAP (builtin_type_void);
  DEPRECATED_REGISTER_GDBARCH_SWAP (builtin_type_char);
  DEPRECATED_REGISTER_GDBARCH_SWAP (builtin_type_short);
  DEPRECATED_REGISTER_GDBARCH_SWAP (builtin_type_int);
  DEPRECATED_REGISTER_GDBARCH_SWAP (builtin_type_long);
  DEPRECATED_REGISTER_GDBARCH_SWAP (builtin_type_long_long);
  DEPRECATED_REGISTER_GDBARCH_SWAP (builtin_type_signed_char);
  DEPRECATED_REGISTER_GDBARCH_SWAP (builtin_type_unsigned_char);
  DEPRECATED_REGISTER_GDBARCH_SWAP (builtin_type_unsigned_short);
  DEPRECATED_REGISTER_GDBARCH_SWAP (builtin_type_unsigned_int);
  DEPRECATED_REGISTER_GDBARCH_SWAP (builtin_type_unsigned_long);
  DEPRECATED_REGISTER_GDBARCH_SWAP (builtin_type_unsigned_long_long);
  DEPRECATED_REGISTER_GDBARCH_SWAP (builtin_type_float);
  DEPRECATED_REGISTER_GDBARCH_SWAP (builtin_type_double);
  DEPRECATED_REGISTER_GDBARCH_SWAP (builtin_type_long_double);
  DEPRECATED_REGISTER_GDBARCH_SWAP (builtin_type_complex);
  DEPRECATED_REGISTER_GDBARCH_SWAP (builtin_type_double_complex);
  DEPRECATED_REGISTER_GDBARCH_SWAP (builtin_type_string);
  DEPRECATED_REGISTER_GDBARCH_SWAP (builtin_type_int8);
  DEPRECATED_REGISTER_GDBARCH_SWAP (builtin_type_uint8);
  DEPRECATED_REGISTER_GDBARCH_SWAP (builtin_type_int16);
  DEPRECATED_REGISTER_GDBARCH_SWAP (builtin_type_uint16);
  DEPRECATED_REGISTER_GDBARCH_SWAP (builtin_type_int32);
  DEPRECATED_REGISTER_GDBARCH_SWAP (builtin_type_uint32);
  DEPRECATED_REGISTER_GDBARCH_SWAP (builtin_type_int64);
  DEPRECATED_REGISTER_GDBARCH_SWAP (builtin_type_uint64);
  DEPRECATED_REGISTER_GDBARCH_SWAP (builtin_type_int128);
  DEPRECATED_REGISTER_GDBARCH_SWAP (builtin_type_uint128);
  DEPRECATED_REGISTER_GDBARCH_SWAP (builtin_type_v4sf);
  DEPRECATED_REGISTER_GDBARCH_SWAP (builtin_type_v4si);
  DEPRECATED_REGISTER_GDBARCH_SWAP (builtin_type_v16qi);
  DEPRECATED_REGISTER_GDBARCH_SWAP (builtin_type_v8qi);
  DEPRECATED_REGISTER_GDBARCH_SWAP (builtin_type_v8hi);
  DEPRECATED_REGISTER_GDBARCH_SWAP (builtin_type_v4hi);
  DEPRECATED_REGISTER_GDBARCH_SWAP (builtin_type_v2si);
  DEPRECATED_REGISTER_GDBARCH_SWAP (builtin_type_v2_double);
  DEPRECATED_REGISTER_GDBARCH_SWAP (builtin_type_v4_float);
  DEPRECATED_REGISTER_GDBARCH_SWAP (builtin_type_v2_int64);
  DEPRECATED_REGISTER_GDBARCH_SWAP (builtin_type_v4_int32);
  DEPRECATED_REGISTER_GDBARCH_SWAP (builtin_type_v8_int16);
  DEPRECATED_REGISTER_GDBARCH_SWAP (builtin_type_v16_int8);
  DEPRECATED_REGISTER_GDBARCH_SWAP (builtin_type_v2_float);
  DEPRECATED_REGISTER_GDBARCH_SWAP (builtin_type_v2_int32);
  DEPRECATED_REGISTER_GDBARCH_SWAP (builtin_type_v8_int8);
  DEPRECATED_REGISTER_GDBARCH_SWAP (builtin_type_v4_int16);
  DEPRECATED_REGISTER_GDBARCH_SWAP (builtin_type_vec128);
  DEPRECATED_REGISTER_GDBARCH_SWAP (builtin_type_vec128i);
  DEPRECATED_REGISTER_GDBARCH_SWAP (builtin_type_void_data_ptr);
  DEPRECATED_REGISTER_GDBARCH_SWAP (builtin_type_void_func_ptr);
  DEPRECATED_REGISTER_GDBARCH_SWAP (builtin_type_CORE_ADDR);
  DEPRECATED_REGISTER_GDBARCH_SWAP (builtin_type_bfd_vma);
  deprecated_register_gdbarch_swap (NULL, 0, build_gdbtypes);

  /* Note: These types do not need to be swapped - they are target
     neutral.  */
  builtin_type_ieee_single_big =
    init_type (TYPE_CODE_FLT, floatformat_ieee_single_big.totalsize / 8,
	       0, "builtin_type_ieee_single_big", NULL);
  TYPE_FLOATFORMAT (builtin_type_ieee_single_big) = &floatformat_ieee_single_big;
  builtin_type_ieee_single_little =
    init_type (TYPE_CODE_FLT, floatformat_ieee_single_little.totalsize / 8,
	       0, "builtin_type_ieee_single_little", NULL);
  TYPE_FLOATFORMAT (builtin_type_ieee_single_little) = &floatformat_ieee_single_little;
  builtin_type_ieee_double_big =
    init_type (TYPE_CODE_FLT, floatformat_ieee_double_big.totalsize / 8,
	       0, "builtin_type_ieee_double_big", NULL);
  TYPE_FLOATFORMAT (builtin_type_ieee_double_big) = &floatformat_ieee_double_big;
  builtin_type_ieee_double_little =
    init_type (TYPE_CODE_FLT, floatformat_ieee_double_little.totalsize / 8,
	       0, "builtin_type_ieee_double_little", NULL);
  TYPE_FLOATFORMAT (builtin_type_ieee_double_little) = &floatformat_ieee_double_little;
  builtin_type_ieee_double_littlebyte_bigword =
    init_type (TYPE_CODE_FLT, floatformat_ieee_double_littlebyte_bigword.totalsize / 8,
	       0, "builtin_type_ieee_double_littlebyte_bigword", NULL);
  TYPE_FLOATFORMAT (builtin_type_ieee_double_littlebyte_bigword) = &floatformat_ieee_double_littlebyte_bigword;
  builtin_type_i387_ext =
    init_type (TYPE_CODE_FLT, floatformat_i387_ext.totalsize / 8,
	       0, "builtin_type_i387_ext", NULL);
  TYPE_FLOATFORMAT (builtin_type_i387_ext) = &floatformat_i387_ext;
  builtin_type_m68881_ext =
    init_type (TYPE_CODE_FLT, floatformat_m68881_ext.totalsize / 8,
	       0, "builtin_type_m68881_ext", NULL);
  TYPE_FLOATFORMAT (builtin_type_m68881_ext) = &floatformat_m68881_ext;
  builtin_type_i960_ext =
    init_type (TYPE_CODE_FLT, floatformat_i960_ext.totalsize / 8,
	       0, "builtin_type_i960_ext", NULL);
  TYPE_FLOATFORMAT (builtin_type_i960_ext) = &floatformat_i960_ext;
  builtin_type_m88110_ext =
    init_type (TYPE_CODE_FLT, floatformat_m88110_ext.totalsize / 8,
	       0, "builtin_type_m88110_ext", NULL);
  TYPE_FLOATFORMAT (builtin_type_m88110_ext) = &floatformat_m88110_ext;
  builtin_type_m88110_harris_ext =
    init_type (TYPE_CODE_FLT, floatformat_m88110_harris_ext.totalsize / 8,
	       0, "builtin_type_m88110_harris_ext", NULL);
  TYPE_FLOATFORMAT (builtin_type_m88110_harris_ext) = &floatformat_m88110_harris_ext;
  builtin_type_arm_ext_big =
    init_type (TYPE_CODE_FLT, floatformat_arm_ext_big.totalsize / 8,
	       0, "builtin_type_arm_ext_big", NULL);
  TYPE_FLOATFORMAT (builtin_type_arm_ext_big) = &floatformat_arm_ext_big;
  builtin_type_arm_ext_littlebyte_bigword =
    init_type (TYPE_CODE_FLT, floatformat_arm_ext_littlebyte_bigword.totalsize / 8,
	       0, "builtin_type_arm_ext_littlebyte_bigword", NULL);
  TYPE_FLOATFORMAT (builtin_type_arm_ext_littlebyte_bigword) = &floatformat_arm_ext_littlebyte_bigword;
  builtin_type_ia64_spill_big =
    init_type (TYPE_CODE_FLT, floatformat_ia64_spill_big.totalsize / 8,
	       0, "builtin_type_ia64_spill_big", NULL);
  TYPE_FLOATFORMAT (builtin_type_ia64_spill_big) = &floatformat_ia64_spill_big;
  builtin_type_ia64_spill_little =
    init_type (TYPE_CODE_FLT, floatformat_ia64_spill_little.totalsize / 8,
	       0, "builtin_type_ia64_spill_little", NULL);
  TYPE_FLOATFORMAT (builtin_type_ia64_spill_little) = &floatformat_ia64_spill_little;
  builtin_type_ia64_quad_big =
    init_type (TYPE_CODE_FLT, floatformat_ia64_quad_big.totalsize / 8,
	       0, "builtin_type_ia64_quad_big", NULL);
  TYPE_FLOATFORMAT (builtin_type_ia64_quad_big) = &floatformat_ia64_quad_big;
  builtin_type_ia64_quad_little =
    init_type (TYPE_CODE_FLT, floatformat_ia64_quad_little.totalsize / 8,
	       0, "builtin_type_ia64_quad_little", NULL);
  TYPE_FLOATFORMAT (builtin_type_ia64_quad_little) = &floatformat_ia64_quad_little;

  add_show_from_set (
		     add_set_cmd ("overload", no_class, var_zinteger, (char *) &overload_debug,
				  "Set debugging of C++ overloading.\n\
			  When enabled, ranking of the functions\n\
			  is displayed.", &setdebuglist),
		     &showdebuglist);
}