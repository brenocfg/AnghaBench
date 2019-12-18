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

/* Variables and functions */
 int SERIAL_TIMEOUT ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  gdb_stderr ; 
 int /*<<< orphan*/  mips_desc ; 
 int /*<<< orphan*/  remote_timeout ; 
 int serial_readchar (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tftp_in_use ; 
 int /*<<< orphan*/  udp_desc ; 
 scalar_t__ udp_in_use ; 

__attribute__((used)) static int
pmon_check_ack (char *mesg)
{
#if defined(DOETXACK)
  int c;

  if (!tftp_in_use)
    {
      c = serial_readchar (udp_in_use ? udp_desc : mips_desc,
			   remote_timeout);
      if ((c == SERIAL_TIMEOUT) || (c != 0x06))
	{
	  fprintf_unfiltered (gdb_stderr,
			      "Failed to receive valid ACK for %s\n", mesg);
	  return (-1);		/* terminate the download */
	}
    }
#endif /* DOETXACK */
  return (0);
}