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
typedef  int /*<<< orphan*/  PTRACE_XFER_TYPE ;
typedef  int /*<<< orphan*/  PTRACE_ARG3_TYPE ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 scalar_t__ CANNOT_STORE_REGISTER (int) ; 
 int DEPRECATED_REGISTER_RAW_SIZE (int) ; 
 int MAX_REGISTER_SIZE ; 
 int PIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PT_WRITE_U ; 
 char* REGISTER_NAME (int) ; 
 int TIDGET (int /*<<< orphan*/ ) ; 
 unsigned int U_REGS_OFFSET ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  perror_with_name (char*) ; 
 int /*<<< orphan*/  ptrace (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regcache_collect (int,char*) ; 
 scalar_t__ register_addr (int,unsigned int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,int) ; 

__attribute__((used)) static void
store_register (int regno)
{
  /* This isn't really an address.  But ptrace thinks of it as one.  */
  CORE_ADDR regaddr;
  char mess[128];		/* For messages */
  int i;
  unsigned int offset;		/* Offset of registers within the u area.  */
  int tid;
  char buf[MAX_REGISTER_SIZE];

  if (CANNOT_STORE_REGISTER (regno))
    {
      return;
    }

  /* Overload thread id onto process id */
  if ((tid = TIDGET (inferior_ptid)) == 0)
    tid = PIDGET (inferior_ptid);	/* no thread id, just use process id */

  offset = U_REGS_OFFSET;

  regaddr = register_addr (regno, offset);

  /* Put the contents of regno into a local buffer */
  regcache_collect (regno, buf);

  /* Store the local buffer into the inferior a chunk at the time. */
  for (i = 0; i < DEPRECATED_REGISTER_RAW_SIZE (regno); i += sizeof (PTRACE_XFER_TYPE))
    {
      errno = 0;
      ptrace (PT_WRITE_U, tid, (PTRACE_ARG3_TYPE) regaddr,
	      *(PTRACE_XFER_TYPE *) (buf + i));
      regaddr += sizeof (PTRACE_XFER_TYPE);
      if (errno != 0)
	{
	  sprintf (mess, "writing register %s (#%d)", 
		   REGISTER_NAME (regno), regno);
	  perror_with_name (mess);
	}
    }
}