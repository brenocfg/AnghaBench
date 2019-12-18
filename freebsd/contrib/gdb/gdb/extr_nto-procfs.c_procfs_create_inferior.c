#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct inheritance {int flags; int /*<<< orphan*/  pgroup; int /*<<< orphan*/  nd; } ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  int pid_t ;
typedef  int /*<<< orphan*/  inherit ;
typedef  int /*<<< orphan*/  flags ;
struct TYPE_2__ {int /*<<< orphan*/ * obfd; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCMD_PROC_SET_FLAG ; 
 int EOK ; 
 int /*<<< orphan*/  ND_LOCAL_NODE ; 
 scalar_t__ ND_NODE_CMP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  O_WRONLY ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  SIG_BLOCK ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  SIG_UNBLOCK ; 
 int /*<<< orphan*/  SOLIB_CREATE_INFERIOR_HOOK (int) ; 
 int SPAWN_EXEC ; 
 int SPAWN_HOLD ; 
 int /*<<< orphan*/  SPAWN_NEWPGROUP ; 
 int SPAWN_SETGROUP ; 
 int SPAWN_SETND ; 
 int STDERR_FILENO ; 
 int STDIN_FILENO ; 
 int STDOUT_FILENO ; 
 int _DEBUG_FLAG_KLC ; 
 scalar_t__ attach_flag ; 
 int /*<<< orphan*/  breakup_args (char*,char**) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  ctl_fd ; 
 int devctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_attach (int /*<<< orphan*/ ) ; 
 char* errno ; 
 int /*<<< orphan*/  error (char*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * exec_bfd ; 
 char* get_exec_file (int) ; 
 char* inferior_io_terminal ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  memset (struct inheritance*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nto_node () ; 
 char** nto_parse_redirection (char**,char**,char**,char**) ; 
 int /*<<< orphan*/  nto_procfs_node ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  pid_to_ptid (int) ; 
 int /*<<< orphan*/  procfs_ops ; 
 int /*<<< orphan*/  push_target (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  safe_strerror (char*) ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int spawnp (char*,int,int*,struct inheritance*,char**,char**) ; 
 int strlen (char*) ; 
 TYPE_1__* symfile_objfile ; 
 int /*<<< orphan*/  target_terminal_init () ; 
 int /*<<< orphan*/  xfree (char*) ; 
 char** xmalloc (int) ; 
 char* xstrdup (char*) ; 

__attribute__((used)) static void
procfs_create_inferior (char *exec_file, char *allargs, char **env)
{
  struct inheritance inherit;
  pid_t pid;
  int flags, errn;
  char **argv, *args;
  char *in = "", *out = "", *err = "";
  int fd, fds[3];
  sigset_t set;

  argv = xmalloc (((strlen (allargs) + 1) / (unsigned) 2 + 2) *
		  sizeof (*argv));
  argv[0] = get_exec_file (1);
  if (!argv[0])
    {
      if (exec_file)
	argv[0] = exec_file;
      else
	return;
    }

  args = xstrdup (allargs);
  breakup_args (args, exec_file ? &argv[1] : &argv[0]);

  argv = nto_parse_redirection (argv, &in, &out, &err);

  fds[0] = STDIN_FILENO;
  fds[1] = STDOUT_FILENO;
  fds[2] = STDERR_FILENO;

  /* If the user specified I/O via gdb's --tty= arg, use it, but only
     if the i/o is not also being specified via redirection.  */
  if (inferior_io_terminal)
    {
      if (!in[0])
	in = inferior_io_terminal;
      if (!out[0])
	out = inferior_io_terminal;
      if (!err[0])
	err = inferior_io_terminal;
    }

  if (in[0])
    {
      fd = open (in, O_RDONLY);
      if (fd == -1)
	perror (in);
      else
	fds[0] = fd;
    }
  if (out[0])
    {
      fd = open (out, O_WRONLY);
      if (fd == -1)
	perror (out);
      else
	fds[1] = fd;
    }
  if (err[0])
    {
      fd = open (err, O_WRONLY);
      if (fd == -1)
	perror (err);
      else
	fds[2] = fd;
    }

  /* Clear any pending SIGUSR1's but keep the behavior the same.  */
  signal (SIGUSR1, signal (SIGUSR1, SIG_IGN));

  sigemptyset (&set);
  sigaddset (&set, SIGUSR1);
  sigprocmask (SIG_UNBLOCK, &set, NULL);

  memset (&inherit, 0, sizeof (inherit));

  if (ND_NODE_CMP (nto_procfs_node, ND_LOCAL_NODE) != 0)
    {
      inherit.nd = nto_node();
      inherit.flags |= SPAWN_SETND;
      inherit.flags &= ~SPAWN_EXEC;
    }
  inherit.flags |= SPAWN_SETGROUP | SPAWN_HOLD;
  inherit.pgroup = SPAWN_NEWPGROUP;
  pid = spawnp (argv[0], 3, fds, &inherit, argv,
		ND_NODE_CMP (nto_procfs_node, ND_LOCAL_NODE) == 0 ? env : 0);
  xfree (args);

  sigprocmask (SIG_BLOCK, &set, NULL);

  if (pid == -1)
    error ("Error spawning %s: %d (%s)", argv[0], errno, safe_strerror (errno));

  if (fds[0] != STDIN_FILENO)
    close (fds[0]);
  if (fds[1] != STDOUT_FILENO)
    close (fds[1]);
  if (fds[2] != STDERR_FILENO)
    close (fds[2]);

  inferior_ptid = do_attach (pid_to_ptid (pid));

  attach_flag = 0;
  flags = _DEBUG_FLAG_KLC;	/* Kill-on-Last-Close flag.  */
  errn = devctl (ctl_fd, DCMD_PROC_SET_FLAG, &flags, sizeof (flags), 0);
  if (errn != EOK)
    {
      /* FIXME: expected warning?  */
      /* warning( "Failed to set Kill-on-Last-Close flag: errno = %d(%s)\n",
         errn, strerror(errn) ); */
    }
  push_target (&procfs_ops);
  target_terminal_init ();

#ifdef SOLIB_CREATE_INFERIOR_HOOK
  if (exec_bfd != NULL
      || (symfile_objfile != NULL && symfile_objfile->obfd != NULL))
    SOLIB_CREATE_INFERIOR_HOOK (pid);
#endif
}