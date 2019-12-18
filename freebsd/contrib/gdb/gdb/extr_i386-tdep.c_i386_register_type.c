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
struct gdbarch {int dummy; } ;

/* Variables and functions */
 int I386_EBP_REGNUM ; 
 int I386_EIP_REGNUM ; 
 int I386_ESP_REGNUM ; 
 struct type* builtin_type_i387_ext ; 
 struct type* builtin_type_int ; 
 struct type* builtin_type_vec128i ; 
 struct type* builtin_type_vec64i ; 
 int /*<<< orphan*/  builtin_type_void ; 
 scalar_t__ i386_fp_regnum_p (int) ; 
 scalar_t__ i386_mmx_regnum_p (struct gdbarch*,int) ; 
 scalar_t__ i386_sse_regnum_p (struct gdbarch*,int) ; 
 struct type* lookup_pointer_type (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct type *
i386_register_type (struct gdbarch *gdbarch, int regnum)
{
  if (regnum == I386_EIP_REGNUM
      || regnum == I386_EBP_REGNUM || regnum == I386_ESP_REGNUM)
    return lookup_pointer_type (builtin_type_void);

  if (i386_fp_regnum_p (regnum))
    return builtin_type_i387_ext;

  if (i386_sse_regnum_p (gdbarch, regnum))
    return builtin_type_vec128i;

  if (i386_mmx_regnum_p (gdbarch, regnum))
    return builtin_type_vec64i;

  return builtin_type_int;
}