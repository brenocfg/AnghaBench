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
typedef  enum type_code { ____Placeholder_type_code } type_code ;

/* Variables and functions */
 scalar_t__ MIPS_EABI ; 
 scalar_t__ MIPS_FPU_NONE ; 
 scalar_t__ MIPS_FPU_TYPE ; 
 int TYPE_CODE (int /*<<< orphan*/ ) ; 
 int TYPE_CODE_FLT ; 
 int TYPE_CODE_STRUCT ; 
 int TYPE_CODE_UNION ; 
 int /*<<< orphan*/  TYPE_FIELD_TYPE (struct type*,int /*<<< orphan*/ ) ; 
 int TYPE_NFIELDS (struct type*) ; 

__attribute__((used)) static int
fp_register_arg_p (enum type_code typecode, struct type *arg_type)
{
  return ((typecode == TYPE_CODE_FLT
	   || (MIPS_EABI
	       && (typecode == TYPE_CODE_STRUCT
		   || typecode == TYPE_CODE_UNION)
	       && TYPE_NFIELDS (arg_type) == 1
	       && TYPE_CODE (TYPE_FIELD_TYPE (arg_type, 0)) == TYPE_CODE_FLT))
	  && MIPS_FPU_TYPE != MIPS_FPU_NONE);
}