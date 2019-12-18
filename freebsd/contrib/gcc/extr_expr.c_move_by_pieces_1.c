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
struct move_by_pieces {unsigned int len; unsigned int offset; scalar_t__ explicit_inc_to; scalar_t__ explicit_inc_from; scalar_t__ reverse; int /*<<< orphan*/  from_addr; int /*<<< orphan*/  to_addr; scalar_t__ to; scalar_t__ from; scalar_t__ autinc_from; scalar_t__ autinc_to; } ;
typedef  int /*<<< orphan*/  rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
typedef  unsigned int HOST_WIDE_INT ;

/* Variables and functions */
 int /*<<< orphan*/  GEN_INT (unsigned int) ; 
 unsigned int GET_MODE_SIZE (int) ; 
 scalar_t__ HAVE_POST_INCREMENT ; 
 scalar_t__ HAVE_PRE_DECREMENT ; 
 int /*<<< orphan*/  NULL_RTX ; 
 int /*<<< orphan*/  adjust_address (scalar_t__,int,unsigned int) ; 
 int /*<<< orphan*/  adjust_automodify_address (scalar_t__,int,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  emit_insn (rtx) ; 
 int /*<<< orphan*/  emit_single_push_insn (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 rtx gen_add2_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 rtx stub1 (rtx,...) ; 

__attribute__((used)) static void
move_by_pieces_1 (rtx (*genfun) (rtx, ...), enum machine_mode mode,
		  struct move_by_pieces *data)
{
  unsigned int size = GET_MODE_SIZE (mode);
  rtx to1 = NULL_RTX, from1;

  while (data->len >= size)
    {
      if (data->reverse)
	data->offset -= size;

      if (data->to)
	{
	  if (data->autinc_to)
	    to1 = adjust_automodify_address (data->to, mode, data->to_addr,
					     data->offset);
	  else
	    to1 = adjust_address (data->to, mode, data->offset);
	}

      if (data->autinc_from)
	from1 = adjust_automodify_address (data->from, mode, data->from_addr,
					   data->offset);
      else
	from1 = adjust_address (data->from, mode, data->offset);

      if (HAVE_PRE_DECREMENT && data->explicit_inc_to < 0)
	emit_insn (gen_add2_insn (data->to_addr,
				  GEN_INT (-(HOST_WIDE_INT)size)));
      if (HAVE_PRE_DECREMENT && data->explicit_inc_from < 0)
	emit_insn (gen_add2_insn (data->from_addr,
				  GEN_INT (-(HOST_WIDE_INT)size)));

      if (data->to)
	emit_insn ((*genfun) (to1, from1));
      else
	{
#ifdef PUSH_ROUNDING
	  emit_single_push_insn (mode, from1, NULL);
#else
	  gcc_unreachable ();
#endif
	}

      if (HAVE_POST_INCREMENT && data->explicit_inc_to > 0)
	emit_insn (gen_add2_insn (data->to_addr, GEN_INT (size)));
      if (HAVE_POST_INCREMENT && data->explicit_inc_from > 0)
	emit_insn (gen_add2_insn (data->from_addr, GEN_INT (size)));

      if (! data->reverse)
	data->offset += size;

      data->len -= size;
    }
}