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
typedef  int /*<<< orphan*/  time_t ;
typedef  int /*<<< orphan*/  section_map_func ;
typedef  int /*<<< orphan*/  buffer ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 scalar_t__ bfd_check_format (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ bfd_get_start_address (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_map_over_sections (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  bfd_object ; 
 int /*<<< orphan*/ * bfd_openr (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_symtab_users () ; 
 scalar_t__ count_section ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  ethernet ; 
 int /*<<< orphan*/ * exec_bfd ; 
 char* get_exec_file (int) ; 
 int /*<<< orphan*/  ignore_packet () ; 
 int /*<<< orphan*/  inferior_ptid ; 
 scalar_t__ load_section ; 
 int /*<<< orphan*/  monitor_expect_prompt (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  monitor_printf (char*) ; 
 int /*<<< orphan*/  null_ptid ; 
 int /*<<< orphan*/  orig_monitor_load (char*,int) ; 
 int /*<<< orphan*/  printf_filtered (char*,long) ; 
 int /*<<< orphan*/  process_read_request (unsigned char*,int) ; 
 int /*<<< orphan*/  report_transfer_performance (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_packet (char,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_long (unsigned char*,long) ; 
 int /*<<< orphan*/  write_pc (scalar_t__) ; 

__attribute__((used)) static void
r3900_load (char *filename, int from_tty)
{
  bfd *abfd;
  unsigned int data_count = 0;
  time_t start_time, end_time;	/* for timing of download */
  int section_count = 0;
  unsigned char buffer[8];

  /* If we are not using the ethernet, use the normal monitor load,
     which sends S-records over the serial link.  */
  if (!ethernet)
    {
      orig_monitor_load (filename, from_tty);
      return;
    }

  /* Open the file.  */
  if (filename == NULL || filename[0] == 0)
    filename = get_exec_file (1);
  abfd = bfd_openr (filename, 0);
  if (!abfd)
    error ("Unable to open file %s\n", filename);
  if (bfd_check_format (abfd, bfd_object) == 0)
    error ("File is not an object file\n");

  /* Output the "vconsi" command to get the monitor in the communication
     state where it will accept a load command.  This will cause
     the monitor to emit a packet before each prompt, so ignore the packet.  */
  monitor_printf ("vconsi\r");
  ignore_packet ();
  monitor_expect_prompt (NULL, 0);

  /* Output the "Rm" (load) command and respond to the subsequent "open"
     packet by sending an ACK packet.  */
  monitor_printf ("Rm\r");
  ignore_packet ();
  send_packet ('a', "", 0, 0);

  /* Output the fast load header (number of sections and starting address).  */
  bfd_map_over_sections ((bfd *) abfd, (section_map_func) count_section,
			 &section_count);
  write_long (&buffer[0], (long) section_count);
  if (exec_bfd)
    write_long (&buffer[4], (long) bfd_get_start_address (exec_bfd));
  else
    write_long (&buffer[4], 0);
  process_read_request (buffer, sizeof (buffer));

  /* Output the section data.  */
  start_time = time (NULL);
  bfd_map_over_sections (abfd, (section_map_func) load_section, &data_count);
  end_time = time (NULL);

  /* Acknowledge the close packet and put the monitor back into
     "normal" mode so it won't send packets any more.  */
  ignore_packet ();
  send_packet ('a', "", 0, 0);
  monitor_expect_prompt (NULL, 0);
  monitor_printf ("vconsx\r");
  monitor_expect_prompt (NULL, 0);

  /* Print start address and download performance information.  */
  printf_filtered ("Start address 0x%lx\n", (long) bfd_get_start_address (abfd));
  report_transfer_performance (data_count, start_time, end_time);

  /* Finally, make the PC point at the start address */
  if (exec_bfd)
    write_pc (bfd_get_start_address (exec_bfd));

  inferior_ptid = null_ptid;		/* No process now */

  /* This is necessary because many things were based on the PC at the
     time that we attached to the monitor, which is no longer valid
     now that we have loaded new code (and just changed the PC).
     Another way to do this might be to call normal_stop, except that
     the stack may not be valid, and things would get horribly
     confused... */
  clear_symtab_users ();
}