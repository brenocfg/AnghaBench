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
 int PEXECUTE_FIRST ; 
 int PEXECUTE_LAST ; 
 int PEXECUTE_SEARCH ; 
 int PEX_LAST ; 
 int PEX_SEARCH ; 
 int /*<<< orphan*/  PEX_USE_PIPES ; 
 int idx ; 
 int /*<<< orphan*/ * pex ; 
 int /*<<< orphan*/ * pex_init (int /*<<< orphan*/ ,char const*,char const*) ; 
 char* pex_run (int /*<<< orphan*/ *,int,char const*,char* const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 

int
pexecute (const char *program, char * const *argv, const char *pname,
	  const char *temp_base, char **errmsg_fmt, char **errmsg_arg,
	  int flags)
{
  const char *errmsg;
  int err;

  if ((flags & PEXECUTE_FIRST) != 0)
    {
      if (pex != NULL)
	{
	  *errmsg_fmt = (char *) "pexecute already in progress";
	  *errmsg_arg = NULL;
	  return -1;
	}
      pex = pex_init (PEX_USE_PIPES, pname, temp_base);
      idx = 0;
    }
  else
    {
      if (pex == NULL)
	{
	  *errmsg_fmt = (char *) "pexecute not in progress";
	  *errmsg_arg = NULL;
	  return -1;
	}
    }

  errmsg = pex_run (pex,
		    (((flags & PEXECUTE_LAST) != 0 ? PEX_LAST : 0)
		     | ((flags & PEXECUTE_SEARCH) != 0 ? PEX_SEARCH : 0)),
		    program, argv, NULL, NULL, &err);
  if (errmsg != NULL)
    {
      *errmsg_fmt = (char *) errmsg;
      *errmsg_arg = NULL;
      return -1;
    }

  /* Instead of a PID, we just return a one-based index into the
     status values.  We avoid zero just because the old pexecute would
     never return it.  */
  return ++idx;
}