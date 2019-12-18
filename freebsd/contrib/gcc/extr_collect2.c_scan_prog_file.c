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
struct pex_obj {int dummy; } ;
typedef  enum pass { ____Placeholder_pass } pass ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ISSPACE (int) ; 
 char* NM_FLAGS ; 
 int PASS_LIB ; 
 int PASS_SECOND ; 
 int /*<<< orphan*/  PEX_USE_PIPES ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGQUIT ; 
 void SIG_IGN (int) ; 
 int /*<<< orphan*/  add_to_list (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  constructors ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  destructors ; 
 int /*<<< orphan*/  do_wait (char*,struct pex_obj*) ; 
 int errno ; 
 int /*<<< orphan*/  fatal (char*,...) ; 
 int /*<<< orphan*/  fatal_perror (char*,...) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 char* fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  frame_tables ; 
 int is_ctor_dtor (char*) ; 
 char* nm_file_name ; 
 struct pex_obj* pex_init (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pex_read_output (struct pex_obj*,int /*<<< orphan*/ ) ; 
 char* pex_run (struct pex_obj*,int /*<<< orphan*/ ,char*,char**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ signal (int /*<<< orphan*/ ,void (*) (int)) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ vflag ; 

__attribute__((used)) static void
scan_prog_file (const char *prog_name, enum pass which_pass)
{
  void (*int_handler) (int);
#ifdef SIGQUIT
  void (*quit_handler) (int);
#endif
  char *real_nm_argv[4];
  const char **nm_argv = (const char **) real_nm_argv;
  int argc = 0;
  struct pex_obj *pex;
  const char *errmsg;
  int err;
  char *p, buf[1024];
  FILE *inf;

  if (which_pass == PASS_SECOND)
    return;

  /* If we do not have an `nm', complain.  */
  if (nm_file_name == 0)
    fatal ("cannot find 'nm'");

  nm_argv[argc++] = nm_file_name;
  if (NM_FLAGS[0] != '\0')
    nm_argv[argc++] = NM_FLAGS;

  nm_argv[argc++] = prog_name;
  nm_argv[argc++] = (char *) 0;

  /* Trace if needed.  */
  if (vflag)
    {
      const char **p_argv;
      const char *str;

      for (p_argv = &nm_argv[0]; (str = *p_argv) != (char *) 0; p_argv++)
	fprintf (stderr, " %s", str);

      fprintf (stderr, "\n");
    }

  fflush (stdout);
  fflush (stderr);

  pex = pex_init (PEX_USE_PIPES, "collect2", NULL);
  if (pex == NULL)
    fatal_perror ("pex_init failed");

  errmsg = pex_run (pex, 0, nm_file_name, real_nm_argv, NULL, NULL, &err);
  if (errmsg != NULL)
    {
      if (err != 0)
	{
	  errno = err;
	  fatal_perror ("%s", errmsg);
	}
      else
	fatal ("%s", errmsg);
    }

  int_handler  = (void (*) (int)) signal (SIGINT,  SIG_IGN);
#ifdef SIGQUIT
  quit_handler = (void (*) (int)) signal (SIGQUIT, SIG_IGN);
#endif

  inf = pex_read_output (pex, 0);
  if (inf == NULL)
    fatal_perror ("can't open nm output");

  if (debug)
    fprintf (stderr, "\nnm output with constructors/destructors.\n");

  /* Read each line of nm output.  */
  while (fgets (buf, sizeof buf, inf) != (char *) 0)
    {
      int ch, ch2;
      char *name, *end;

      /* If it contains a constructor or destructor name, add the name
	 to the appropriate list.  */

      for (p = buf; (ch = *p) != '\0' && ch != '\n' && ch != '_'; p++)
	if (ch == ' ' && p[1] == 'U' && p[2] == ' ')
	  break;

      if (ch != '_')
	continue;

      name = p;
      /* Find the end of the symbol name.
	 Do not include `|', because Encore nm can tack that on the end.  */
      for (end = p; (ch2 = *end) != '\0' && !ISSPACE (ch2) && ch2 != '|';
	   end++)
	continue;


      *end = '\0';
      switch (is_ctor_dtor (name))
	{
	case 1:
	  if (which_pass != PASS_LIB)
	    add_to_list (&constructors, name);
	  break;

	case 2:
	  if (which_pass != PASS_LIB)
	    add_to_list (&destructors, name);
	  break;

	case 3:
	  if (which_pass != PASS_LIB)
	    fatal ("init function found in object %s", prog_name);
#ifndef LD_INIT_SWITCH
	  add_to_list (&constructors, name);
#endif
	  break;

	case 4:
	  if (which_pass != PASS_LIB)
	    fatal ("fini function found in object %s", prog_name);
#ifndef LD_FINI_SWITCH
	  add_to_list (&destructors, name);
#endif
	  break;

	case 5:
	  if (which_pass != PASS_LIB)
	    add_to_list (&frame_tables, name);
	  break;

	default:		/* not a constructor or destructor */
	  continue;
	}

      if (debug)
	fprintf (stderr, "\t%s\n", buf);
    }

  if (debug)
    fprintf (stderr, "\n");

  do_wait (nm_file_name, pex);

  signal (SIGINT,  int_handler);
#ifdef SIGQUIT
  signal (SIGQUIT, quit_handler);
#endif
}