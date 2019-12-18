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
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
#define  SERIAL_TIMEOUT 128 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stderr ; 
 int /*<<< orphan*/  mips_desc ; 
 int mips_readchar (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  paddr_u (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remote_timeout ; 
 int /*<<< orphan*/  serial_write (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
send_srec (char *srec, int len, CORE_ADDR addr)
{
  while (1)
    {
      int ch;

      serial_write (mips_desc, srec, len);

      ch = mips_readchar (remote_timeout);

      switch (ch)
	{
	case SERIAL_TIMEOUT:
	  error ("Timeout during download.");
	  break;
	case 0x6:		/* ACK */
	  return;
	case 0x15:		/* NACK */
	  fprintf_unfiltered (gdb_stderr, "Download got a NACK at byte %s!  Retrying.\n", paddr_u (addr));
	  continue;
	default:
	  error ("Download got unexpected ack char: 0x%x, retrying.\n", ch);
	}
    }
}