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
struct regcache {int dummy; } ;
struct gdbarch {int dummy; } ;
typedef  enum return_value_convention { ____Placeholder_return_value_convention } return_value_convention ;

/* Variables and functions */
 int RETURN_VALUE_STRUCT_CONVENTION ; 
 scalar_t__ TYPE_CODE (struct type*) ; 
 scalar_t__ TYPE_CODE_STRUCT ; 
 scalar_t__ TYPE_CODE_UNION ; 
 int TYPE_LENGTH (struct type*) ; 
 scalar_t__ TYPE_VECTOR (struct type*) ; 
 int ppc_sysv_abi_broken_return_value (struct gdbarch*,struct type*,struct regcache*,void*,void const*) ; 

__attribute__((used)) static enum return_value_convention
ppcnbsd_return_value (struct gdbarch *gdbarch, struct type *valtype,
		      struct regcache *regcache, void *readbuf,
		      const void *writebuf)
{
  if ((TYPE_CODE (valtype) == TYPE_CODE_STRUCT
       || TYPE_CODE (valtype) == TYPE_CODE_UNION)
      && !((TYPE_LENGTH (valtype) == 16 || TYPE_LENGTH (valtype) == 8)
	    && TYPE_VECTOR (valtype))
      && !(TYPE_LENGTH (valtype) == 1
	   || TYPE_LENGTH (valtype) == 2
	   || TYPE_LENGTH (valtype) == 4
	   || TYPE_LENGTH (valtype) == 8))
    return RETURN_VALUE_STRUCT_CONVENTION;
  else
    return ppc_sysv_abi_broken_return_value (gdbarch, valtype, regcache,
					     readbuf, writebuf);
}