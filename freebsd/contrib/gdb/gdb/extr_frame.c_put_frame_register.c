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
struct gdbarch {int dummy; } ;
struct frame_info {int dummy; } ;
typedef  enum lval_type { ____Placeholder_lval_type } lval_type ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int MAX_REGISTER_SIZE ; 
 int /*<<< orphan*/  current_regcache ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  frame_register (struct frame_info*,int,int*,int*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 
 struct gdbarch* get_frame_arch (struct frame_info*) ; 
#define  lval_memory 129 
#define  lval_register 128 
 int /*<<< orphan*/  memcpy (char*,void const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regcache_cooked_write (int /*<<< orphan*/ ,int,void const*) ; 
 int /*<<< orphan*/  register_size (struct gdbarch*,int) ; 
 int /*<<< orphan*/  write_memory (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void
put_frame_register (struct frame_info *frame, int regnum, const void *buf)
{
  struct gdbarch *gdbarch = get_frame_arch (frame);
  int realnum;
  int optim;
  enum lval_type lval;
  CORE_ADDR addr;
  frame_register (frame, regnum, &optim, &lval, &addr, &realnum, NULL);
  if (optim)
    error ("Attempt to assign to a value that was optimized out.");
  switch (lval)
    {
    case lval_memory:
      {
	/* FIXME: write_memory doesn't yet take constant buffers.
           Arrrg!  */
	char tmp[MAX_REGISTER_SIZE];
	memcpy (tmp, buf, register_size (gdbarch, regnum));
	write_memory (addr, tmp, register_size (gdbarch, regnum));
	break;
      }
    case lval_register:
      regcache_cooked_write (current_regcache, realnum, buf);
      break;
    default:
      error ("Attempt to assign to an unmodifiable value.");
    }
}