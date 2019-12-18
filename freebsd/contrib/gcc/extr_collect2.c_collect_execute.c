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

/* Variables and functions */
 int PEX_LAST ; 
 int PEX_SEARCH ; 
 scalar_t__ debug ; 
 int errno ; 
 int /*<<< orphan*/  fatal (char*,char const*) ; 
 int /*<<< orphan*/  fatal_perror (char*,...) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  notice (char*,char const*) ; 
 struct pex_obj* pex_init (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 char* pex_run (struct pex_obj*,int,char*,char**,char const*,char const*,int*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ vflag ; 

struct pex_obj *
collect_execute (const char *prog, char **argv, const char *outname,
		 const char *errname)
{
  struct pex_obj *pex;
  const char *errmsg;
  int err;

  if (vflag || debug)
    {
      char **p_argv;
      const char *str;

      if (argv[0])
	fprintf (stderr, "%s", argv[0]);
      else
	notice ("[cannot find %s]", prog);

      for (p_argv = &argv[1]; (str = *p_argv) != (char *) 0; p_argv++)
	fprintf (stderr, " %s", str);

      fprintf (stderr, "\n");
    }

  fflush (stdout);
  fflush (stderr);

  /* If we cannot find a program we need, complain error.  Do this here
     since we might not end up needing something that we could not find.  */

  if (argv[0] == 0)
    fatal ("cannot find '%s'", prog);

  pex = pex_init (0, "collect2", NULL);
  if (pex == NULL)
    fatal_perror ("pex_init failed");

  errmsg = pex_run (pex, PEX_LAST | PEX_SEARCH, argv[0], argv, outname,
		    errname, &err);
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

  return pex;
}