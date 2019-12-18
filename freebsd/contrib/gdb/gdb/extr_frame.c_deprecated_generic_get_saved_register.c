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
struct frame_info {int dummy; } ;
typedef  enum lval_type { ____Placeholder_lval_type } lval_type ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  DEPRECATED_FRAME_INIT_SAVED_REGS (struct frame_info*) ; 
 scalar_t__ DEPRECATED_REGISTER_BYTE (int) ; 
 int /*<<< orphan*/  DEPRECATED_REGISTER_RAW_SIZE (int) ; 
 scalar_t__ DUMMY_FRAME ; 
 int SP_REGNUM ; 
 int /*<<< orphan*/  deprecated_find_dummy_frame_regcache (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__* deprecated_get_frame_saved_regs (struct frame_info*) ; 
 int /*<<< orphan*/  deprecated_read_register_gen (int,char*) ; 
 int /*<<< orphan*/  error (char*) ; 
 scalar_t__ frame_relative_level (struct frame_info*) ; 
 int /*<<< orphan*/  get_frame_base (struct frame_info*) ; 
 int /*<<< orphan*/  get_frame_pc (struct frame_info*) ; 
 scalar_t__ get_frame_type (struct frame_info*) ; 
 struct frame_info* get_next_frame (struct frame_info*) ; 
 int lval_memory ; 
 int lval_register ; 
 int not_lval ; 
 int /*<<< orphan*/  read_memory (scalar_t__,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regcache_raw_read (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  store_unsigned_integer (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  target_has_registers ; 

void
deprecated_generic_get_saved_register (char *raw_buffer, int *optimized,
				       CORE_ADDR *addrp,
				       struct frame_info *frame, int regnum,
				       enum lval_type *lval)
{
  if (!target_has_registers)
    error ("No registers.");

  /* Normal systems don't optimize out things with register numbers.  */
  if (optimized != NULL)
    *optimized = 0;

  if (addrp)			/* default assumption: not found in memory */
    *addrp = 0;

  /* Note: since the current frame's registers could only have been
     saved by frames INTERIOR TO the current frame, we skip examining
     the current frame itself: otherwise, we would be getting the
     previous frame's registers which were saved by the current frame.  */

  if (frame != NULL)
    {
      for (frame = get_next_frame (frame);
	   frame_relative_level (frame) >= 0;
	   frame = get_next_frame (frame))
	{
	  if (get_frame_type (frame) == DUMMY_FRAME)
	    {
	      if (lval)		/* found it in a CALL_DUMMY frame */
		*lval = not_lval;
	      if (raw_buffer)
		/* FIXME: cagney/2002-06-26: This should be via the
		   gdbarch_register_read() method so that it, on the
		   fly, constructs either a raw or pseudo register
		   from the raw register cache.  */
		regcache_raw_read
		  (deprecated_find_dummy_frame_regcache (get_frame_pc (frame),
							 get_frame_base (frame)),
		   regnum, raw_buffer);
	      return;
	    }

	  DEPRECATED_FRAME_INIT_SAVED_REGS (frame);
	  if (deprecated_get_frame_saved_regs (frame) != NULL
	      && deprecated_get_frame_saved_regs (frame)[regnum] != 0)
	    {
	      if (lval)		/* found it saved on the stack */
		*lval = lval_memory;
	      if (regnum == SP_REGNUM)
		{
		  if (raw_buffer)	/* SP register treated specially */
		    /* NOTE: cagney/2003-05-09: In-line store_address
                       with it's body - store_unsigned_integer.  */
		    store_unsigned_integer (raw_buffer,
					    DEPRECATED_REGISTER_RAW_SIZE (regnum),
					    deprecated_get_frame_saved_regs (frame)[regnum]);
		}
	      else
		{
		  if (addrp)	/* any other register */
		    *addrp = deprecated_get_frame_saved_regs (frame)[regnum];
		  if (raw_buffer)
		    read_memory (deprecated_get_frame_saved_regs (frame)[regnum], raw_buffer,
				 DEPRECATED_REGISTER_RAW_SIZE (regnum));
		}
	      return;
	    }
	}
    }

  /* If we get thru the loop to this point, it means the register was
     not saved in any frame.  Return the actual live-register value.  */

  if (lval)			/* found it in a live register */
    *lval = lval_register;
  if (addrp)
    *addrp = DEPRECATED_REGISTER_BYTE (regnum);
  if (raw_buffer)
    deprecated_read_register_gen (regnum, raw_buffer);
}