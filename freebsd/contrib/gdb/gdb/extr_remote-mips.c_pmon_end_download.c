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
struct stat {int st_mode; } ;

/* Variables and functions */
#define  MON_LSI 128 
 int S_IROTH ; 
 int /*<<< orphan*/  chmod (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mips_expect_download (char*) ; 
 int mips_monitor ; 
 int /*<<< orphan*/  mips_send_command (char*,int) ; 
 int /*<<< orphan*/  pmon_check_ack (char*) ; 
 int /*<<< orphan*/  pmon_check_entry_address (char*,int) ; 
 int /*<<< orphan*/  pmon_check_total (int) ; 
 int /*<<< orphan*/  remove (int /*<<< orphan*/ ) ; 
 scalar_t__ stat (int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/ * tftp_file ; 
 scalar_t__ tftp_in_use ; 
 int /*<<< orphan*/  tftp_localname ; 
 char* tftp_name ; 
 int /*<<< orphan*/  xfree (char*) ; 
 char* xmalloc (scalar_t__) ; 

__attribute__((used)) static void
pmon_end_download (int final, int bintotal)
{
  char hexnumber[9];		/* includes '\0' space */

  if (tftp_in_use)
    {
      static char *load_cmd_prefix = "load -b -s ";
      char *cmd;
      struct stat stbuf;

      /* Close off the temporary file containing the load data.  */
      fclose (tftp_file);
      tftp_file = NULL;

      /* Make the temporary file readable by the world.  */
      if (stat (tftp_localname, &stbuf) == 0)
	chmod (tftp_localname, stbuf.st_mode | S_IROTH);

      /* Must reinitialize the board to prevent PMON from crashing.  */
      mips_send_command ("initEther\r", -1);

      /* Send the load command.  */
      cmd = xmalloc (strlen (load_cmd_prefix) + strlen (tftp_name) + 2);
      strcpy (cmd, load_cmd_prefix);
      strcat (cmd, tftp_name);
      strcat (cmd, "\r");
      mips_send_command (cmd, 0);
      xfree (cmd);
      if (!mips_expect_download ("Downloading from "))
	return;
      if (!mips_expect_download (tftp_name))
	return;
      if (!mips_expect_download (", ^C to abort\r\n"))
	return;
    }

  /* Wait for the stuff that PMON prints after the load has completed.
     The timeout value for use in the tftp case (15 seconds) was picked
     arbitrarily but might be too small for really large downloads. FIXME. */
  switch (mips_monitor)
    {
    case MON_LSI:
      pmon_check_ack ("termination");
      pmon_check_entry_address ("Entry address is ", final);
      if (!pmon_check_total (bintotal))
	return;
      break;
    default:
      pmon_check_entry_address ("Entry Address  = ", final);
      pmon_check_ack ("termination");
      if (!pmon_check_total (bintotal))
	return;
      break;
    }

  if (tftp_in_use)
    remove (tftp_localname);	/* Remove temporary file */
}