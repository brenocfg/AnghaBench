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
 int /*<<< orphan*/  LOAD_CMD ; 
 int /*<<< orphan*/  LOAD_CMD_UDP ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mips_expect (char*) ; 
 int /*<<< orphan*/  mips_send_command (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror_with_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * tftp_file ; 
 scalar_t__ tftp_in_use ; 
 int /*<<< orphan*/  tftp_localname ; 
 scalar_t__ udp_in_use ; 

__attribute__((used)) static void
pmon_start_download (void)
{
  if (tftp_in_use)
    {
      /* Create the temporary download file.  */
      if ((tftp_file = fopen (tftp_localname, "w")) == NULL)
	perror_with_name (tftp_localname);
    }
  else
    {
      mips_send_command (udp_in_use ? LOAD_CMD_UDP : LOAD_CMD, 0);
      mips_expect ("Downloading from ");
      mips_expect (udp_in_use ? "udp" : "tty0");
      mips_expect (", ^C to abort\r\n");
    }
}