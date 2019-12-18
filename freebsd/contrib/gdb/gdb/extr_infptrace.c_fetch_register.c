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
 scalar_t__ CANNOT_FETCH_REGISTER (int) ; 
 int DEPRECATED_REGISTER_RAW_SIZE (int) ; 
 int MAX_REGISTER_SIZE ; 
 int PIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PT_READ_U ; 
 char* REGISTER_NAME (int) ; 
 int TIDGET (int /*<<< orphan*/ ) ; 
 unsigned int U_REGS_OFFSET ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int /*<<< orphan*/  perror_with_name (char*) ; 
 int /*<<< orphan*/  ptrace (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ register_addr (int,unsigned int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,int) ; 
 int /*<<< orphan*/  supply_register (int,char*) ; 

__attribute__((used)) static void
fetch_register (int regno)
{
  /* This isn't really an address.  But ptrace thinks of it as one.  */
  CORE_ADDR regaddr;
  char mess[128];		/* For messages */
  int i;
  unsigned int offset;		/* Offset of registers within the u area.  */
  char buf[MAX_REGISTER_SIZE];
  int tid;

  if (CANNOT_FETCH_REGISTER (regno))
    {
      memset (buf, '\0', DEPRECATED_REGISTER_RAW_SIZE (regno));	/* Supply zeroes */
      supply_register (regno, buf);
      return;
    }

  /* Overload thread id onto process id */
  if ((tid = TIDGET (inferior_ptid)) == 0)
    tid = PIDGET (inferior_ptid);	/* no thread id, just use process id */

  offset = U_REGS_OFFSET;

  regaddr = register_addr (regno, offset);
  for (i = 0; i < DEPRECATED_REGISTER_RAW_SIZE (regno); i += sizeof (PTRACE_XFER_TYPE))
    {
      errno = 0;
      *(PTRACE_XFER_TYPE *) & buf[i] = ptrace (PT_READ_U, tid,
					       (PTRACE_ARG3_TYPE) regaddr, 0);
      regaddr += sizeof (PTRACE_XFER_TYPE);
      if (errno != 0)
	{
	  sprintf (mess, "reading register %s (#%d)", 
		   REGISTER_NAME (regno), regno);
	  perror_with_name (mess);
	}
    }
  supply_register (regno, buf);
}