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
struct frame_info {int dummy; } ;

/* Variables and functions */
 int I386_MAX_REGISTER_SIZE ; 
 scalar_t__ TYPE_CODE (struct type*) ; 
 scalar_t__ TYPE_CODE_FLT ; 
 int /*<<< orphan*/  builtin_type_i387_ext ; 
 int /*<<< orphan*/  convert_typed_floating (void const*,struct type*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i386_fp_regnum_p (int) ; 
 int /*<<< orphan*/  put_frame_register (struct frame_info*,int,char*) ; 
 int /*<<< orphan*/  warning (char*) ; 

void
i387_value_to_register (struct frame_info *frame, int regnum,
			struct type *type, const void *from)
{
  char to[I386_MAX_REGISTER_SIZE];

  gdb_assert (i386_fp_regnum_p (regnum));

  /* We only support floating-point values.  */
  if (TYPE_CODE (type) != TYPE_CODE_FLT)
    {
      warning ("Cannot convert non-floating-point type "
	       "to floating-point register value.");
      return;
    }

  /* Convert from TYPE.  This should be a no-op if TYPE is equivalent
     to the extended floating-point format used by the FPU.  */
  convert_typed_floating (from, type, to, builtin_type_i387_ext);
  put_frame_register (frame, regnum, to);
}