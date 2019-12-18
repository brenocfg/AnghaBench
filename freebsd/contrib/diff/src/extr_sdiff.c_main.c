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
struct line_filter {int dummy; } ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* DEFAULT_DIFF_PROGRAM ; 
#define  DIFF_PROGRAM_OPTION 131 
 int EINTR ; 
 int ENOENT ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  EXIT_TROUBLE ; 
#define  HELP_OPTION 130 
 int /*<<< orphan*/  LC_ALL ; 
 int /*<<< orphan*/  LOCALEDIR ; 
 int /*<<< orphan*/  PACKAGE ; 
 int /*<<< orphan*/  PACKAGE_NAME ; 
 int /*<<< orphan*/  PACKAGE_VERSION ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIG_BLOCK ; 
 scalar_t__ SIG_DFL ; 
 scalar_t__ SIG_IGN ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int STDOUT_FILENO ; 
#define  STRIP_TRAILING_CR_OPTION 129 
#define  TABSIZE_OPTION 128 
 int /*<<< orphan*/  WEXITSTATUS (int) ; 
 int /*<<< orphan*/  _exit (int) ; 
 int /*<<< orphan*/  bindtextdomain (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_stack_action (int /*<<< orphan*/ ) ; 
 scalar_t__ catchsig ; 
 int /*<<< orphan*/  check_child_status (int,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  check_stdout () ; 
 int /*<<< orphan*/  checksigs () ; 
 int /*<<< orphan*/  ck_fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ck_fopen (char const*,char*) ; 
 int /*<<< orphan*/  cleanup ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  diffarg (char*) ; 
 char** diffargv ; 
 scalar_t__ diffpid ; 
 int diraccess (char*) ; 
 int /*<<< orphan*/  dup2 (int,int) ; 
 char const* editor_program ; 
 int errno ; 
 int /*<<< orphan*/  execvp (char*,char**) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit_failure ; 
 int /*<<< orphan*/  exiterr () ; 
 char* expand_name (char*,int,char*) ; 
 int /*<<< orphan*/  fatal (char*) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getenv (char*) ; 
 int getopt_long (int,char**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handler_index_of_SIGINT ; 
 int /*<<< orphan*/  handler_index_of_SIGPIPE ; 
 scalar_t__ initial_handler (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initialize_main (int*,char***) ; 
 int interact (struct line_filter*,struct line_filter*,char const*,struct line_filter*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lf_init (struct line_filter*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  longopts ; 
 char* optarg ; 
 int optind ; 
 char const* output ; 
 int pclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perror_fatal (char*) ; 
 scalar_t__ pipe (int*) ; 
 int /*<<< orphan*/ * popen (char*,char*) ; 
 char* program_name ; 
 scalar_t__ quote_system_arg (char*,char*) ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal_handler (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stdout ; 
 int suppress_common_lines ; 
 int /*<<< orphan*/  textdomain (int /*<<< orphan*/ ) ; 
 scalar_t__ tmpname ; 
 int /*<<< orphan*/  trapsigs () ; 
 int /*<<< orphan*/  try_help (char*,char*) ; 
 int /*<<< orphan*/  unlink (scalar_t__) ; 
 int /*<<< orphan*/  untrapsig (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  version_etc (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ vfork () ; 
 scalar_t__ waitpid (scalar_t__,int*,int /*<<< orphan*/ ) ; 
 char* xmalloc (size_t) ; 

int
main (int argc, char *argv[])
{
  int opt;
  char const *prog;

  exit_failure = EXIT_TROUBLE;
  initialize_main (&argc, &argv);
  program_name = argv[0];
  setlocale (LC_ALL, "");
  bindtextdomain (PACKAGE, LOCALEDIR);
  textdomain (PACKAGE);
  c_stack_action (cleanup);

  prog = getenv ("EDITOR");
  if (prog)
    editor_program = prog;

  diffarg (DEFAULT_DIFF_PROGRAM);

  /* parse command line args */
  while ((opt = getopt_long (argc, argv, "abBdEHiI:lo:stvw:W", longopts, 0))
	 != -1)
    {
      switch (opt)
	{
	case 'a':
	  diffarg ("-a");
	  break;

	case 'b':
	  diffarg ("-b");
	  break;

	case 'B':
	  diffarg ("-B");
	  break;

	case 'd':
	  diffarg ("-d");
	  break;

	case 'E':
	  diffarg ("-E");
	  break;

	case 'H':
	  diffarg ("-H");
	  break;

	case 'i':
	  diffarg ("-i");
	  break;

	case 'I':
	  diffarg ("-I");
	  diffarg (optarg);
	  break;

	case 'l':
	  diffarg ("--left-column");
	  break;

	case 'o':
	  output = optarg;
	  break;

	case 's':
	  suppress_common_lines = true;
	  break;

	case 't':
	  diffarg ("-t");
	  break;

	case 'v':
	  version_etc (stdout, "sdiff", PACKAGE_NAME, PACKAGE_VERSION,
		       "Thomas Lord", (char *) 0);
	  check_stdout ();
	  return EXIT_SUCCESS;

	case 'w':
	  diffarg ("-W");
	  diffarg (optarg);
	  break;

	case 'W':
	  diffarg ("-w");
	  break;

	case DIFF_PROGRAM_OPTION:
	  diffargv[0] = optarg;
	  break;

	case HELP_OPTION:
	  usage ();
	  check_stdout ();
	  return EXIT_SUCCESS;

	case STRIP_TRAILING_CR_OPTION:
	  diffarg ("--strip-trailing-cr");
	  break;

	case TABSIZE_OPTION:
	  diffarg ("--tabsize");
	  diffarg (optarg);
	  break;

	default:
	  try_help (0, 0);
	}
    }

  if (argc - optind != 2)
    {
      if (argc - optind < 2)
	try_help ("missing operand after `%s'", argv[argc - 1]);
      else
	try_help ("extra operand `%s'", argv[optind + 2]);
    }

  if (! output)
    {
      /* easy case: diff does everything for us */
      if (suppress_common_lines)
	diffarg ("--suppress-common-lines");
      diffarg ("-y");
      diffarg ("--");
      diffarg (argv[optind]);
      diffarg (argv[optind + 1]);
      diffarg (0);
      execvp (diffargv[0], (char **) diffargv);
      perror_fatal (diffargv[0]);
    }
  else
    {
      char const *lname, *rname;
      FILE *left, *right, *out, *diffout;
      bool interact_ok;
      struct line_filter lfilt;
      struct line_filter rfilt;
      struct line_filter diff_filt;
      bool leftdir = diraccess (argv[optind]);
      bool rightdir = diraccess (argv[optind + 1]);

      if (leftdir & rightdir)
	fatal ("both files to be compared are directories");

      lname = expand_name (argv[optind], leftdir, argv[optind + 1]);
      left = ck_fopen (lname, "r");
      rname = expand_name (argv[optind + 1], rightdir, argv[optind]);
      right = ck_fopen (rname, "r");
      out = ck_fopen (output, "w");

      diffarg ("--sdiff-merge-assist");
      diffarg ("--");
      diffarg (argv[optind]);
      diffarg (argv[optind + 1]);
      diffarg (0);

      trapsigs ();

#if ! (HAVE_WORKING_FORK || HAVE_WORKING_VFORK)
      {
	size_t cmdsize = 1;
	char *p, *command;
	int i;

	for (i = 0;  diffargv[i];  i++)
	  cmdsize += quote_system_arg (0, diffargv[i]) + 1;
	command = p = xmalloc (cmdsize);
	for (i = 0;  diffargv[i];  i++)
	  {
	    p += quote_system_arg (p, diffargv[i]);
	    *p++ = ' ';
	  }
	p[-1] = 0;
	errno = 0;
	diffout = popen (command, "r");
	if (! diffout)
	  perror_fatal (command);
	free (command);
      }
#else
      {
	int diff_fds[2];
# if HAVE_WORKING_VFORK
	sigset_t procmask;
	sigset_t blocked;
# endif

	if (pipe (diff_fds) != 0)
	  perror_fatal ("pipe");

# if HAVE_WORKING_VFORK
	/* Block SIGINT and SIGPIPE.  */
	sigemptyset (&blocked);
	sigaddset (&blocked, SIGINT);
	sigaddset (&blocked, SIGPIPE);
	sigprocmask (SIG_BLOCK, &blocked, &procmask);
# endif
	diffpid = vfork ();
	if (diffpid < 0)
	  perror_fatal ("fork");
	if (! diffpid)
	  {
	    /* Alter the child's SIGINT and SIGPIPE handlers;
	       this may munge the parent.
	       The child ignores SIGINT in case the user interrupts the editor.
	       The child does not ignore SIGPIPE, even if the parent does.  */
	    if (initial_handler (handler_index_of_SIGINT) != SIG_IGN)
	      signal_handler (SIGINT, SIG_IGN);
	    signal_handler (SIGPIPE, SIG_DFL);
# if HAVE_WORKING_VFORK
	    /* Stop blocking SIGINT and SIGPIPE in the child.  */
	    sigprocmask (SIG_SETMASK, &procmask, 0);
# endif
	    close (diff_fds[0]);
	    if (diff_fds[1] != STDOUT_FILENO)
	      {
		dup2 (diff_fds[1], STDOUT_FILENO);
		close (diff_fds[1]);
	      }

	    execvp (diffargv[0], (char **) diffargv);
	    _exit (errno == ENOENT ? 127 : 126);
	  }

# if HAVE_WORKING_VFORK
	/* Restore the parent's SIGINT and SIGPIPE behavior.  */
	if (initial_handler (handler_index_of_SIGINT) != SIG_IGN)
	  signal_handler (SIGINT, catchsig);
	if (initial_handler (handler_index_of_SIGPIPE) != SIG_IGN)
	  signal_handler (SIGPIPE, catchsig);
	else
	  signal_handler (SIGPIPE, SIG_IGN);

	/* Stop blocking SIGINT and SIGPIPE in the parent.  */
	sigprocmask (SIG_SETMASK, &procmask, 0);
# endif

	close (diff_fds[1]);
	diffout = fdopen (diff_fds[0], "r");
	if (! diffout)
	  perror_fatal ("fdopen");
      }
#endif

      lf_init (&diff_filt, diffout);
      lf_init (&lfilt, left);
      lf_init (&rfilt, right);

      interact_ok = interact (&diff_filt, &lfilt, lname, &rfilt, rname, out);

      ck_fclose (left);
      ck_fclose (right);
      ck_fclose (out);

      {
	int wstatus;
	int werrno = 0;

#if ! (HAVE_WORKING_FORK || HAVE_WORKING_VFORK)
	wstatus = pclose (diffout);
	if (wstatus == -1)
	  werrno = errno;
#else
	ck_fclose (diffout);
	while (waitpid (diffpid, &wstatus, 0) < 0)
	  if (errno == EINTR)
	    checksigs ();
	  else
	    perror_fatal ("waitpid");
	diffpid = 0;
#endif

	if (tmpname)
	  {
	    unlink (tmpname);
	    tmpname = 0;
	  }

	if (! interact_ok)
	  exiterr ();

	check_child_status (werrno, wstatus, EXIT_FAILURE, diffargv[0]);
	untrapsig (0);
	checksigs ();
	exit (WEXITSTATUS (wstatus));
      }
    }
  return EXIT_SUCCESS;			/* Fool `-Wall'.  */
}