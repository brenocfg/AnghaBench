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
struct frame_info {struct frame_info* prev; } ;
typedef  enum lval_type { ____Placeholder_lval_type } lval_type ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  DEPRECATED_FRAME_INIT_SAVED_REGS (struct frame_info*) ; 
 int /*<<< orphan*/  DEPRECATED_FRAME_INIT_SAVED_REGS_P () ; 
 int DEPRECATED_REGISTER_RAW_SIZE (int) ; 
 int NUM_PSEUDO_REGS ; 
 int NUM_REGS ; 
 int SP_REGNUM ; 
 scalar_t__* deprecated_get_frame_saved_regs (struct frame_info*) ; 
 void* frame_obstack_zalloc (int) ; 
 int /*<<< orphan*/  frame_register_unwind (struct frame_info*,int,int*,int*,scalar_t__*,int*,void*) ; 
 int /*<<< orphan*/  gdb_assert (int /*<<< orphan*/ ) ; 
 int lval_memory ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 int not_lval ; 
 int /*<<< orphan*/  read_memory (scalar_t__,void*,int) ; 
 int /*<<< orphan*/  store_unsigned_integer (void*,int,scalar_t__) ; 

__attribute__((used)) static void
legacy_saved_regs_prev_register (struct frame_info *next_frame,
				 void **this_prologue_cache,
				 int regnum, int *optimizedp,
				 enum lval_type *lvalp, CORE_ADDR *addrp,
				 int *realnump, void *bufferp)
{
  /* HACK: New code is passed the next frame and this cache.
     Unfortunately, old code expects this frame.  Since this is a
     backward compatibility hack, cheat by walking one level along the
     prologue chain to the frame the old code expects.

     Do not try this at home.  Professional driver, closed course.  */
  struct frame_info *frame = next_frame->prev;
  gdb_assert (frame != NULL);

  if (deprecated_get_frame_saved_regs (frame) == NULL)
    {
      /* If nothing's initialized the saved regs, do it now.  */
      gdb_assert (DEPRECATED_FRAME_INIT_SAVED_REGS_P ());
      DEPRECATED_FRAME_INIT_SAVED_REGS (frame);
      gdb_assert (deprecated_get_frame_saved_regs (frame) != NULL);
    }

  if (deprecated_get_frame_saved_regs (frame) != NULL
      && deprecated_get_frame_saved_regs (frame)[regnum] != 0)
    {
      if (regnum == SP_REGNUM)
	{
	  /* SP register treated specially.  */
	  *optimizedp = 0;
	  *lvalp = not_lval;
	  *addrp = 0;
	  *realnump = -1;
	  if (bufferp != NULL)
	    /* NOTE: cagney/2003-05-09: In-lined store_address with
               it's body - store_unsigned_integer.  */
	    store_unsigned_integer (bufferp, DEPRECATED_REGISTER_RAW_SIZE (regnum),
				    deprecated_get_frame_saved_regs (frame)[regnum]);
	}
      else
	{
	  /* Any other register is saved in memory, fetch it but cache
             a local copy of its value.  */
	  *optimizedp = 0;
	  *lvalp = lval_memory;
	  *addrp = deprecated_get_frame_saved_regs (frame)[regnum];
	  *realnump = -1;
	  if (bufferp != NULL)
	    {
#if 1
	      /* Save each register value, as it is read in, in a
                 frame based cache.  */
	      void **regs = (*this_prologue_cache);
	      if (regs == NULL)
		{
		  int sizeof_cache = ((NUM_REGS + NUM_PSEUDO_REGS)
				      * sizeof (void *));
		  regs = frame_obstack_zalloc (sizeof_cache);
		  (*this_prologue_cache) = regs;
		}
	      if (regs[regnum] == NULL)
		{
		  regs[regnum]
		    = frame_obstack_zalloc (DEPRECATED_REGISTER_RAW_SIZE (regnum));
		  read_memory (deprecated_get_frame_saved_regs (frame)[regnum], regs[regnum],
			       DEPRECATED_REGISTER_RAW_SIZE (regnum));
		}
	      memcpy (bufferp, regs[regnum], DEPRECATED_REGISTER_RAW_SIZE (regnum));
#else
	      /* Read the value in from memory.  */
	      read_memory (deprecated_get_frame_saved_regs (frame)[regnum], bufferp,
			   DEPRECATED_REGISTER_RAW_SIZE (regnum));
#endif
	    }
	}
      return;
    }

  /* No luck.  Assume this and the next frame have the same register
     value.  Pass the unwind request down the frame chain to the next
     frame.  Hopefully that frame will find the register's location.  */
  frame_register_unwind (next_frame, regnum, optimizedp, lvalp, addrp,
			 realnump, bufferp);
}