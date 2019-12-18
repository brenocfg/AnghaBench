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
struct target_ops {int dummy; } ;
struct ptrace_io_desc {char* piod_addr; int piod_len; void* piod_offs; int /*<<< orphan*/  piod_op; } ;
struct mem_attrib {int dummy; } ;
struct cleanup {int dummy; } ;
typedef  int /*<<< orphan*/  caddr_t ;
typedef  int PTRACE_XFER_TYPE ;
typedef  int /*<<< orphan*/  PTRACE_ARG3_TYPE ;
typedef  int CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR_INSN_CACHE () ; 
 scalar_t__ EINVAL ; 
 int GDB_MAX_ALLOCA ; 
 int /*<<< orphan*/  PIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIOD_READ_D ; 
 int /*<<< orphan*/  PIOD_WRITE_D ; 
 int /*<<< orphan*/  PT_IO ; 
 int /*<<< orphan*/  PT_READ_I ; 
 int /*<<< orphan*/  PT_WRITE_D ; 
 int /*<<< orphan*/  PT_WRITE_I ; 
 int /*<<< orphan*/  QUIT ; 
 scalar_t__ alloca (int) ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  inferior_ptid ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int ptrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xfree ; 
 scalar_t__ xmalloc (int) ; 

int
child_xfer_memory (CORE_ADDR memaddr, char *myaddr, int len, int write,
		   struct mem_attrib *attrib, struct target_ops *target)
{
  int i;
  /* Round starting address down to longword boundary.  */
  CORE_ADDR addr = memaddr & -(CORE_ADDR) sizeof (PTRACE_XFER_TYPE);
  /* Round ending address up; get number of longwords that makes.  */
  int count = ((((memaddr + len) - addr) + sizeof (PTRACE_XFER_TYPE) - 1)
	       / sizeof (PTRACE_XFER_TYPE));
  int alloc = count * sizeof (PTRACE_XFER_TYPE);
  PTRACE_XFER_TYPE *buffer;
  struct cleanup *old_chain = NULL;

#ifdef PT_IO
  /* OpenBSD 3.1, NetBSD 1.6 and FreeBSD 5.0 have a new PT_IO request
     that promises to be much more efficient in reading and writing
     data in the traced process's address space.  */

  {
    struct ptrace_io_desc piod;

    /* NOTE: We assume that there are no distinct address spaces for
       instruction and data.  */
    piod.piod_op = write ? PIOD_WRITE_D : PIOD_READ_D;
    piod.piod_offs = (void *) memaddr;
    piod.piod_addr = myaddr;
    piod.piod_len = len;

    if (ptrace (PT_IO, PIDGET (inferior_ptid), (caddr_t) &piod, 0) == -1)
      {
	/* If the PT_IO request is somehow not supported, fallback on
           using PT_WRITE_D/PT_READ_D.  Otherwise we will return zero
           to indicate failure.  */
	if (errno != EINVAL)
	  return 0;
      }
    else
      {
	/* Return the actual number of bytes read or written.  */
	return piod.piod_len;
      }
  }
#endif

  /* Allocate buffer of that many longwords.  */
  if (len < GDB_MAX_ALLOCA)
    {
      buffer = (PTRACE_XFER_TYPE *) alloca (alloc);
    }
  else
    {
      buffer = (PTRACE_XFER_TYPE *) xmalloc (alloc);
      old_chain = make_cleanup (xfree, buffer);
    }

  if (write)
    {
      /* Fill start and end extra bytes of buffer with existing memory
         data.  */
      if (addr != memaddr || len < (int) sizeof (PTRACE_XFER_TYPE))
	{
	  /* Need part of initial word -- fetch it.  */
	  buffer[0] = ptrace (PT_READ_I, PIDGET (inferior_ptid), 
			      (PTRACE_ARG3_TYPE) addr, 0);
	}

      if (count > 1)		/* FIXME, avoid if even boundary.  */
	{
	  buffer[count - 1] =
	    ptrace (PT_READ_I, PIDGET (inferior_ptid),
		    ((PTRACE_ARG3_TYPE)
		     (addr + (count - 1) * sizeof (PTRACE_XFER_TYPE))), 0);
	}

      /* Copy data to be written over corresponding part of buffer.  */
      memcpy ((char *) buffer + (memaddr & (sizeof (PTRACE_XFER_TYPE) - 1)),
	      myaddr, len);

      /* Write the entire buffer.  */
      for (i = 0; i < count; i++, addr += sizeof (PTRACE_XFER_TYPE))
	{
	  errno = 0;
	  ptrace (PT_WRITE_D, PIDGET (inferior_ptid), 
		  (PTRACE_ARG3_TYPE) addr, buffer[i]);
	  if (errno)
	    {
	      /* Using the appropriate one (I or D) is necessary for
	         Gould NP1, at least.  */
	      errno = 0;
	      ptrace (PT_WRITE_I, PIDGET (inferior_ptid), 
		      (PTRACE_ARG3_TYPE) addr, buffer[i]);
	    }
	  if (errno)
	    return 0;
	}
#ifdef CLEAR_INSN_CACHE
      CLEAR_INSN_CACHE ();
#endif
    }
  else
    {
      /* Read all the longwords.  */
      for (i = 0; i < count; i++, addr += sizeof (PTRACE_XFER_TYPE))
	{
	  errno = 0;
	  buffer[i] = ptrace (PT_READ_I, PIDGET (inferior_ptid),
			      (PTRACE_ARG3_TYPE) addr, 0);
	  if (errno)
	    return 0;
	  QUIT;
	}

      /* Copy appropriate bytes out of the buffer.  */
      memcpy (myaddr,
	      (char *) buffer + (memaddr & (sizeof (PTRACE_XFER_TYPE) - 1)),
	      len);
    }

  if (old_chain != NULL)
    do_cleanups (old_chain);
  return len;
}