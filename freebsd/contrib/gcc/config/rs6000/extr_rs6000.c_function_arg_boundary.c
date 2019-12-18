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
typedef  scalar_t__ tree ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 scalar_t__ ABI_V4 ; 
 scalar_t__ ALTIVEC_VECTOR_MODE (int) ; 
 int BLKmode ; 
 scalar_t__ DEFAULT_ABI ; 
 int GET_MODE_SIZE (int) ; 
 int PARM_BOUNDARY ; 
 scalar_t__ SPE_VECTOR_MODE (int) ; 
 scalar_t__ TARGET_FPRS ; 
 scalar_t__ TARGET_HARD_FLOAT ; 
 int TFmode ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 int TYPE_ALIGN (scalar_t__) ; 
 scalar_t__ VECTOR_TYPE ; 
 int int_size_in_bytes (scalar_t__) ; 
 scalar_t__ rs6000_darwin64_abi ; 

int
function_arg_boundary (enum machine_mode mode, tree type)
{
  if (DEFAULT_ABI == ABI_V4
      && (GET_MODE_SIZE (mode) == 8
	  || (TARGET_HARD_FLOAT
	      && TARGET_FPRS
	      && mode == TFmode)))
    return 64;
  else if (SPE_VECTOR_MODE (mode)
	   || (type && TREE_CODE (type) == VECTOR_TYPE
	       && int_size_in_bytes (type) >= 8
	       && int_size_in_bytes (type) < 16))
    return 64;
  else if (ALTIVEC_VECTOR_MODE (mode)
	   || (type && TREE_CODE (type) == VECTOR_TYPE
	       && int_size_in_bytes (type) >= 16))
    return 128;
  else if (rs6000_darwin64_abi && mode == BLKmode
	   && type && TYPE_ALIGN (type) > 64)
    return 128;
  else
    return PARM_BOUNDARY;
}