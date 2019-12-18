#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
struct cleanup {int dummy; } ;
typedef  scalar_t__ file_ptr ;
typedef  int bfd_vma ;
typedef  scalar_t__ bfd_size_type ;
struct TYPE_17__ {TYPE_2__* sections; } ;
typedef  TYPE_1__ bfd ;
struct TYPE_18__ {struct TYPE_18__* next; } ;
typedef  TYPE_2__ asection ;

/* Variables and functions */
 int /*<<< orphan*/  QUIT ; 
 int SEC_LOAD ; 
 int /*<<< orphan*/  WRITESIZE ; 
 int /*<<< orphan*/  bfd_check_format (TYPE_1__*,int /*<<< orphan*/ ) ; 
 char* bfd_errmsg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_get_error () ; 
 int /*<<< orphan*/  bfd_get_section_contents (TYPE_1__*,TYPE_2__*,char*,scalar_t__,int) ; 
 int bfd_get_section_flags (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  bfd_get_section_name (TYPE_1__*,TYPE_2__*) ; 
 scalar_t__ bfd_get_section_size (TYPE_2__*) ; 
 int bfd_get_section_vma (TYPE_1__*,TYPE_2__*) ; 
 int bfd_get_start_address (TYPE_1__*) ; 
 int /*<<< orphan*/  bfd_object ; 
 TYPE_1__* bfd_openr (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_symtab_users () ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  e7000_desc ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (char*,char*,...) ; 
 TYPE_1__* exec_bfd ; 
 int /*<<< orphan*/  expect (char*) ; 
 int /*<<< orphan*/  expect_prompt () ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stderr ; 
 int /*<<< orphan*/  gdb_stdout ; 
 int /*<<< orphan*/  generic_load (char*,int) ; 
 char* get_exec_file (int) ; 
 int /*<<< orphan*/  gnutarget ; 
 int /*<<< orphan*/  inferior_ptid ; 
 scalar_t__ isspace (char) ; 
 struct cleanup* make_cleanup_bfd_close (TYPE_1__*) ; 
 int min (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  null_ptid ; 
 int /*<<< orphan*/  paddr_nz (int) ; 
 int /*<<< orphan*/  paddr_u (scalar_t__) ; 
 int /*<<< orphan*/  perror_with_name (char*) ; 
 int /*<<< orphan*/  printf_filtered (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf_unfiltered (char*,...) ; 
 int /*<<< orphan*/  puts_e7000debug (char*) ; 
 int remote_timeout ; 
 int /*<<< orphan*/  report_transfer_performance (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  safe_strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ serial_write (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 int timeout ; 
 int /*<<< orphan*/  using_tcp ; 
 int /*<<< orphan*/  write_e7000 (char*) ; 
 int /*<<< orphan*/  write_pc (int) ; 

__attribute__((used)) static void
e7000_load (char *args, int from_tty)
{
  struct cleanup *old_chain;
  asection *section;
  bfd *pbfd;
  bfd_vma entry;
#define WRITESIZE 0x1000
  char buf[2 + 4 + 4 + WRITESIZE];	/* `DT' + <addr> + <len> + <data> */
  char *filename;
  int quiet;
  int nostart;
  time_t start_time, end_time;	/* Start and end times of download */
  unsigned long data_count;	/* Number of bytes transferred to memory */
  int oldtimeout = timeout;

  timeout = remote_timeout;


  /* FIXME! change test to test for type of download */
  if (!using_tcp)
    {
      generic_load (args, from_tty);
      return;
    }

  /* for direct tcp connections, we can do a fast binary download */
  buf[0] = 'D';
  buf[1] = 'T';
  quiet = 0;
  nostart = 0;
  filename = NULL;

  while (*args != '\000')
    {
      char *arg;

      while (isspace (*args))
	args++;

      arg = args;

      while ((*args != '\000') && !isspace (*args))
	args++;

      if (*args != '\000')
	*args++ = '\000';

      if (*arg != '-')
	filename = arg;
      else if (strncmp (arg, "-quiet", strlen (arg)) == 0)
	quiet = 1;
      else if (strncmp (arg, "-nostart", strlen (arg)) == 0)
	nostart = 1;
      else
	error ("unknown option `%s'", arg);
    }

  if (!filename)
    filename = get_exec_file (1);

  pbfd = bfd_openr (filename, gnutarget);
  if (pbfd == NULL)
    {
      perror_with_name (filename);
      return;
    }
  old_chain = make_cleanup_bfd_close (pbfd);

  if (!bfd_check_format (pbfd, bfd_object))
    error ("\"%s\" is not an object file: %s", filename,
	   bfd_errmsg (bfd_get_error ()));

  start_time = time (NULL);
  data_count = 0;

  puts_e7000debug ("mw\r");

  expect ("\nOK");

  for (section = pbfd->sections; section; section = section->next)
    {
      if (bfd_get_section_flags (pbfd, section) & SEC_LOAD)
	{
	  bfd_vma section_address;
	  bfd_size_type section_size;
	  file_ptr fptr;

	  section_address = bfd_get_section_vma (pbfd, section);
	  section_size = bfd_get_section_size (section);

	  if (!quiet)
	    printf_filtered ("[Loading section %s at 0x%s (%s bytes)]\n",
			     bfd_get_section_name (pbfd, section),
			     paddr_nz (section_address),
			     paddr_u (section_size));

	  fptr = 0;

	  data_count += section_size;

	  while (section_size > 0)
	    {
	      int count;
	      static char inds[] = "|/-\\";
	      static int k = 0;

	      QUIT;

	      count = min (section_size, WRITESIZE);

	      buf[2] = section_address >> 24;
	      buf[3] = section_address >> 16;
	      buf[4] = section_address >> 8;
	      buf[5] = section_address;

	      buf[6] = count >> 24;
	      buf[7] = count >> 16;
	      buf[8] = count >> 8;
	      buf[9] = count;

	      bfd_get_section_contents (pbfd, section, buf + 10, fptr, count);

	      if (serial_write (e7000_desc, buf, count + 10))
		fprintf_unfiltered (gdb_stderr,
				    "e7000_load: serial_write failed: %s\n",
				    safe_strerror (errno));

	      expect ("OK");

	      if (!quiet)
		{
		  printf_unfiltered ("\r%c", inds[k++ % 4]);
		  gdb_flush (gdb_stdout);
		}

	      section_address += count;
	      fptr += count;
	      section_size -= count;
	    }
	}
    }

  write_e7000 ("ED");

  expect_prompt ();

  end_time = time (NULL);

/* Finally, make the PC point at the start address */

  if (exec_bfd)
    write_pc (bfd_get_start_address (exec_bfd));

  inferior_ptid = null_ptid;	/* No process now */

/* This is necessary because many things were based on the PC at the time that
   we attached to the monitor, which is no longer valid now that we have loaded
   new code (and just changed the PC).  Another way to do this might be to call
   normal_stop, except that the stack may not be valid, and things would get
   horribly confused... */

  clear_symtab_users ();

  if (!nostart)
    {
      entry = bfd_get_start_address (pbfd);

      if (!quiet)
	printf_unfiltered ("[Starting %s at 0x%s]\n", filename, paddr_nz (entry));

/*      start_routine (entry); */
    }

  report_transfer_performance (data_count, start_time, end_time);

  do_cleanups (old_chain);
  timeout = oldtimeout;
}