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
typedef  int /*<<< orphan*/  udot_val ;
typedef  int /*<<< orphan*/  TTRACE_ARG_TYPE ;

/* Variables and functions */
 int KERNEL_U_SIZE ; 
 int /*<<< orphan*/  PIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TT_LWP_RUREGS ; 
 int /*<<< orphan*/  TT_NIL ; 
 int call_ttrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  perror_with_name (char*) ; 
 int /*<<< orphan*/  printf_filtered (char*,...) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  target_has_execution ; 

__attribute__((used)) static void
udot_info (void)
{
  int udot_off;			/* Offset into user struct */
  int udot_val;			/* Value from user struct at udot_off */
  char mess[128];		/* For messages */

  if (!target_has_execution)
    {
      error ("The program is not being run.");
    }

#if !defined (KERNEL_U_SIZE)

  /* Adding support for this command is easy.  Typically you just add a
     routine, called "kernel_u_size" that returns the size of the user
     struct, to the appropriate *-nat.c file and then add to the native
     config file "#define KERNEL_U_SIZE kernel_u_size()" */
  error ("Don't know how large ``struct user'' is in this version of gdb.");

#else

  for (udot_off = 0; udot_off < KERNEL_U_SIZE; udot_off += sizeof (udot_val))
    {
      if ((udot_off % 24) == 0)
	{
	  if (udot_off > 0)
	    {
	      printf_filtered ("\n");
	    }
	  printf_filtered ("%04x:", udot_off);
	}
      udot_val = call_ttrace (TT_LWP_RUREGS,
			      PIDGET (inferior_ptid),
			      (TTRACE_ARG_TYPE) udot_off,
			      TT_NIL,
			      TT_NIL);
      if (errno != 0)
	{
	  sprintf (mess, "\nreading user struct at offset 0x%x", udot_off);
	  perror_with_name (mess);
	}
      /* Avoid using nonportable (?) "*" in print specs */
      printf_filtered (sizeof (int) == 4 ? " 0x%08x" : " 0x%16x", udot_val);
    }
  printf_filtered ("\n");

#endif
}