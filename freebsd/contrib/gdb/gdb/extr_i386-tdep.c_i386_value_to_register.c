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
 int TYPE_LENGTH (struct type*) ; 
 int /*<<< orphan*/  current_gdbarch ; 
 int /*<<< orphan*/  gdb_assert (int) ; 
 scalar_t__ i386_fp_regnum_p (int) ; 
 int i386_next_regnum (int) ; 
 int /*<<< orphan*/  i387_value_to_register (struct frame_info*,int,struct type*,void const*) ; 
 int /*<<< orphan*/  put_frame_register (struct frame_info*,int,char const*) ; 
 int register_size (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
i386_value_to_register (struct frame_info *frame, int regnum,
			struct type *type, const void *from)
{
  int len = TYPE_LENGTH (type);
  const char *buf = from;

  if (i386_fp_regnum_p (regnum))
    {
      i387_value_to_register (frame, regnum, type, from);
      return;
    }

  /* Write a value spread accross multiple registers.  */

  gdb_assert (len > 4 && len % 4 == 0);

  while (len > 0)
    {
      gdb_assert (regnum != -1);
      gdb_assert (register_size (current_gdbarch, regnum) == 4);

      put_frame_register (frame, regnum, buf);
      regnum = i386_next_regnum (regnum);
      len -= 4;
      buf += 4;
    }
}