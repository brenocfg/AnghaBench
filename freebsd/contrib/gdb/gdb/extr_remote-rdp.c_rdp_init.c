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
typedef  scalar_t__ time_t ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_ENDIAN_BIG ; 
 int /*<<< orphan*/  BFD_ENDIAN_LITTLE ; 
 int /*<<< orphan*/  QUIT ; 
 int RDP_OPEN ; 
 int RDP_OPEN_TYPE_COLD ; 
 int RDP_OPEN_TYPE_RETURN_SEX ; 
 int RDP_OPEN_TYPE_WARM ; 
#define  RDP_RESET 132 
#define  RDP_RES_VALUE 131 
#define  RDP_RES_VALUE_BIG_ENDIAN 130 
#define  RDP_RES_VALUE_LITTLE_ENDIAN 129 
#define  SERIAL_TIMEOUT 128 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  gdb_stdlog ; 
 int /*<<< orphan*/  io ; 
 int /*<<< orphan*/  isgraph (int) ; 
 int /*<<< orphan*/  printf_filtered (char*) ; 
 int /*<<< orphan*/  printf_unfiltered (char*,...) ; 
 int /*<<< orphan*/  put_byte (int) ; 
 int /*<<< orphan*/  put_word (int /*<<< orphan*/ ) ; 
 scalar_t__ remote_debug ; 
 int /*<<< orphan*/  serial_flush_input (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_flush_output (int /*<<< orphan*/ ) ; 
 int serial_readchar (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  target_byte_order ; 
 scalar_t__ time (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
rdp_init (int cold, int tty)
{
  int sync = 0;
  int type = cold ? RDP_OPEN_TYPE_COLD : RDP_OPEN_TYPE_WARM;
  int baudtry = 9600;

  time_t now = time (0);
  time_t stop_time = now + 10;	/* Try and sync for 10 seconds, then give up */


  while (time (0) < stop_time && !sync)
    {
      int restype;
      QUIT;

      serial_flush_input (io);
      serial_flush_output (io);

      if (tty)
	printf_unfiltered ("Trying to connect at %d baud.\n", baudtry);

      /*
         ** It seems necessary to reset an EmbeddedICE to get it going.
         ** This has the side benefit of displaying the startup banner.
       */
      if (cold)
	{
	  put_byte (RDP_RESET);
	  while ((restype = serial_readchar (io, 1)) > 0)
	    {
	      switch (restype)
		{
		case SERIAL_TIMEOUT:
		  break;
		case RDP_RESET:
		  /* Sent at start of reset process: ignore */
		  break;
		default:
		  printf_unfiltered ("%c", isgraph (restype) ? restype : ' ');
		  break;
		}
	    }

	  if (restype == 0)
	    {
	      /* Got end-of-banner mark */
	      printf_filtered ("\n");
	    }
	}

      put_byte (RDP_OPEN);

      put_byte (type | RDP_OPEN_TYPE_RETURN_SEX);
      put_word (0);

      while (!sync && (restype = serial_readchar (io, 1)) > 0)
	{
	  if (remote_debug)
	    fprintf_unfiltered (gdb_stdlog, "[%02x]\n", restype);

	  switch (restype)
	    {
	    case SERIAL_TIMEOUT:
	      break;

	    case RDP_RESET:
	      while ((restype = serial_readchar (io, 1)) == RDP_RESET)
		;
	      do
		{
		  printf_unfiltered ("%c", isgraph (restype) ? restype : ' ');
		}
	      while ((restype = serial_readchar (io, 1)) > 0);

	      if (tty)
		{
		  printf_unfiltered ("\nThe board has sent notification that it was reset.\n");
		  printf_unfiltered ("Waiting for it to settle down...\n");
		}
	      sleep (3);
	      if (tty)
		printf_unfiltered ("\nTrying again.\n");
	      cold = 0;
	      break;

	    default:
	      break;

	    case RDP_RES_VALUE:
	      {
		int resval = serial_readchar (io, 1);

		if (remote_debug)
		  fprintf_unfiltered (gdb_stdlog, "[%02x]\n", resval);

		switch (resval)
		  {
		  case SERIAL_TIMEOUT:
		    break;
		  case RDP_RES_VALUE_LITTLE_ENDIAN:
#if 0
		    /* FIXME: cagney/2003-11-22: Ever since the ARM
                       was multi-arched (in 2002-02-08), this
                       assignment has had no effect.  There needs to
                       be some sort of check/decision based on the
                       current architecture's byte-order vs the remote
                       target's byte order.  For the moment disable
                       the assignment to keep things building.  */
		    target_byte_order = BFD_ENDIAN_LITTLE;
#endif
		    sync = 1;
		    break;
		  case RDP_RES_VALUE_BIG_ENDIAN:
#if 0
		    /* FIXME: cagney/2003-11-22: Ever since the ARM
                       was multi-arched (in 2002-02-08), this
                       assignment has had no effect.  There needs to
                       be some sort of check/decision based on the
                       current architecture's byte-order vs the remote
                       target's byte order.  For the moment disable
                       the assignment to keep things building.  */
		    target_byte_order = BFD_ENDIAN_BIG;
#endif
		    sync = 1;
		    break;
		  default:
		    break;
		  }
	      }
	    }
	}
    }

  if (!sync)
    {
      error ("Couldn't reset the board, try pressing the reset button");
    }
}