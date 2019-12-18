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
struct stat {int dummy; } ;
typedef  int pid_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int ENOENT ; 
 int EXIT_TROUBLE ; 
 int INT_MAX ; 
 size_t MAX (int,int /*<<< orphan*/ ) ; 
 int PTRDIFF_MAX ; 
 size_t SIZE_MAX ; 
 int /*<<< orphan*/  STAT_BLOCKSIZE (struct stat) ; 
 int STDOUT_FILENO ; 
 int WEXITSTATUS (int) ; 
 scalar_t__ WIFEXITED (int) ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  _exit (int) ; 
 size_t block_read (int,char*,size_t) ; 
 scalar_t__ close (int) ; 
 char const* diff_program ; 
 int /*<<< orphan*/  dup2 (int,int) ; 
 int errno ; 
 int /*<<< orphan*/  error (int,int,char*,char const*,int) ; 
 int /*<<< orphan*/  execvp (char const*,char**) ; 
 int /*<<< orphan*/  fatal (char*) ; 
 int fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 int pclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perror_with_exit (char*) ; 
 scalar_t__ pipe (int*) ; 
 int /*<<< orphan*/ * popen (char*,char*) ; 
 int quote_system_arg (char*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 scalar_t__ strip_trailing_cr ; 
 scalar_t__ text ; 
 int vfork () ; 
 scalar_t__ waitpid (int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xalloc_die () ; 
 char* xmalloc (size_t) ; 
 char* xrealloc (char*,size_t) ; 

__attribute__((used)) static char *
read_diff (char const *filea,
	   char const *fileb,
	   char **output_placement)
{
  char *diff_result;
  size_t current_chunk_size, total;
  int fd, wstatus, status;
  int werrno = 0;
  struct stat pipestat;

#if HAVE_WORKING_FORK || HAVE_WORKING_VFORK

  char const *argv[9];
  char const **ap;
  int fds[2];
  pid_t pid;

  ap = argv;
  *ap++ = diff_program;
  if (text)
    *ap++ = "-a";
  if (strip_trailing_cr)
    *ap++ = "--strip-trailing-cr";
  *ap++ = "--horizon-lines=100";
  *ap++ = "--";
  *ap++ = filea;
  *ap++ = fileb;
  *ap = 0;

  if (pipe (fds) != 0)
    perror_with_exit ("pipe");

  pid = vfork ();
  if (pid == 0)
    {
      /* Child */
      close (fds[0]);
      if (fds[1] != STDOUT_FILENO)
	{
	  dup2 (fds[1], STDOUT_FILENO);
	  close (fds[1]);
	}

      /* The cast to (char **) is needed for portability to older
	 hosts with a nonstandard prototype for execvp.  */
      execvp (diff_program, (char **) argv);

      _exit (errno == ENOENT ? 127 : 126);
    }

  if (pid == -1)
    perror_with_exit ("fork");

  close (fds[1]);		/* Prevent erroneous lack of EOF */
  fd = fds[0];

#else

  FILE *fpipe;
  char const args[] = " --horizon-lines=100 -- ";
  char *command = xmalloc (quote_system_arg (0, diff_program)
			   + sizeof "-a"
			   + sizeof "--strip-trailing-cr"
			   + sizeof args - 1
			   + quote_system_arg (0, filea) + 1
			   + quote_system_arg (0, fileb) + 1);
  char *p = command;
  p += quote_system_arg (p, diff_program);
  if (text)
    {
      strcpy (p, " -a");
      p += 3;
    }
  if (strip_trailing_cr)
    {
      strcpy (p, " --strip-trailing-cr");
      p += 20;
    }
  strcpy (p, args);
  p += sizeof args - 1;
  p += quote_system_arg (p, filea);
  *p++ = ' ';
  p += quote_system_arg (p, fileb);
  *p = 0;
  errno = 0;
  fpipe = popen (command, "r");
  if (!fpipe)
    perror_with_exit (command);
  free (command);
  fd = fileno (fpipe);

#endif

  if (fstat (fd, &pipestat) != 0)
    perror_with_exit ("fstat");
  current_chunk_size = MAX (1, STAT_BLOCKSIZE (pipestat));
  diff_result = xmalloc (current_chunk_size);
  total = 0;

  for (;;)
    {
      size_t bytes_to_read = current_chunk_size - total;
      size_t bytes = block_read (fd, diff_result + total, bytes_to_read);
      total += bytes;
      if (bytes != bytes_to_read)
	{
	  if (bytes == SIZE_MAX)
	    perror_with_exit (_("read failed"));
	  break;
	}
      if (PTRDIFF_MAX / 2 <= current_chunk_size)
	xalloc_die ();
      current_chunk_size *= 2;
      diff_result = xrealloc (diff_result, current_chunk_size);
    }

  if (total != 0 && diff_result[total-1] != '\n')
    fatal ("invalid diff format; incomplete last line");

  *output_placement = diff_result;

#if ! (HAVE_WORKING_FORK || HAVE_WORKING_VFORK)

  wstatus = pclose (fpipe);
  if (wstatus == -1)
    werrno = errno;

#else

  if (close (fd) != 0)
    perror_with_exit ("close");
  if (waitpid (pid, &wstatus, 0) < 0)
    perror_with_exit ("waitpid");

#endif

  status = ! werrno && WIFEXITED (wstatus) ? WEXITSTATUS (wstatus) : INT_MAX;

  if (EXIT_TROUBLE <= status)
    error (EXIT_TROUBLE, werrno,
	   _(status == 126
	     ? "subsidiary program `%s' could not be invoked"
	     : status == 127
	     ? "subsidiary program `%s' not found"
	     : status == INT_MAX
	     ? "subsidiary program `%s' failed"
	     : "subsidiary program `%s' failed (exit status %d)"),
	   diff_program, status);

  return diff_result + total;
}