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
struct mem_attrib {int dummy; } ;
typedef  scalar_t__ TTRACE_XFER_TYPE ;
typedef  int /*<<< orphan*/  TTRACE_ARG_TYPE ;
typedef  int CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  PIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QUIT ; 
 int /*<<< orphan*/  TT_LWP_RDTEXT ; 
 int /*<<< orphan*/  TT_LWP_WRDATA ; 
 int /*<<< orphan*/  TT_LWP_WRTEXT ; 
 int /*<<< orphan*/  TT_NIL ; 
 scalar_t__ alloca (int) ; 
 scalar_t__ call_ttrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 

int
child_xfer_memory (CORE_ADDR memaddr, char *myaddr, int len, int write,
		   struct mem_attrib *attrib,
		   struct target_ops *target)
{
  int i;
  /* Round starting address down to longword boundary.  */
  CORE_ADDR addr = memaddr & -(CORE_ADDR) sizeof (TTRACE_XFER_TYPE);
  /* Round ending address up; get number of longwords that makes.  */
  int count
  = (((memaddr + len) - addr) + sizeof (TTRACE_XFER_TYPE) - 1)
  / sizeof (TTRACE_XFER_TYPE);
  /* Allocate buffer of that many longwords.  */
  /* FIXME (alloca): This code, cloned from infptrace.c, is unsafe
     because it uses alloca to allocate a buffer of arbitrary size.
     For very large xfers, this could crash GDB's stack.  */
  TTRACE_XFER_TYPE *buffer
    = (TTRACE_XFER_TYPE *) alloca (count * sizeof (TTRACE_XFER_TYPE));

  if (write)
    {
      /* Fill start and end extra bytes of buffer with existing memory data.  */

      if (addr != memaddr || len < (int) sizeof (TTRACE_XFER_TYPE))
	{
	  /* Need part of initial word -- fetch it.  */
	  buffer[0] = call_ttrace (TT_LWP_RDTEXT,
				   PIDGET (inferior_ptid),
				   (TTRACE_ARG_TYPE) addr,
				   TT_NIL,
				   TT_NIL);
	}

      if (count > 1)		/* FIXME, avoid if even boundary */
	{
	  buffer[count - 1] = call_ttrace (TT_LWP_RDTEXT,
					   PIDGET (inferior_ptid),
					   ((TTRACE_ARG_TYPE)
			  (addr + (count - 1) * sizeof (TTRACE_XFER_TYPE))),
					   TT_NIL,
					   TT_NIL);
	}

      /* Copy data to be written over corresponding part of buffer */

      memcpy ((char *) buffer + (memaddr & (sizeof (TTRACE_XFER_TYPE) - 1)),
	      myaddr,
	      len);

      /* Write the entire buffer.  */

      for (i = 0; i < count; i++, addr += sizeof (TTRACE_XFER_TYPE))
	{
	  errno = 0;
	  call_ttrace (TT_LWP_WRDATA,
		       PIDGET (inferior_ptid),
		       (TTRACE_ARG_TYPE) addr,
		       (TTRACE_ARG_TYPE) buffer[i],
		       TT_NIL);
	  if (errno)
	    {
	      /* Using the appropriate one (I or D) is necessary for
	         Gould NP1, at least.  */
	      errno = 0;
	      call_ttrace (TT_LWP_WRTEXT,
			   PIDGET (inferior_ptid),
			   (TTRACE_ARG_TYPE) addr,
			   (TTRACE_ARG_TYPE) buffer[i],
			   TT_NIL);
	    }
	  if (errno)
	    return 0;
	}
    }
  else
    {
      /* Read all the longwords */
      for (i = 0; i < count; i++, addr += sizeof (TTRACE_XFER_TYPE))
	{
	  errno = 0;
	  buffer[i] = call_ttrace (TT_LWP_RDTEXT,
				   PIDGET (inferior_ptid),
				   (TTRACE_ARG_TYPE) addr,
				   TT_NIL,
				   TT_NIL);
	  if (errno)
	    return 0;
	  QUIT;
	}

      /* Copy appropriate bytes out of the buffer.  */
      memcpy (myaddr,
	      (char *) buffer + (memaddr & (sizeof (TTRACE_XFER_TYPE) - 1)),
	      len);
    }
  return len;
}