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
 int /*<<< orphan*/  pex_free (struct pex_obj*) ; 
 int /*<<< orphan*/  pex_get_status (struct pex_obj*,int,int*) ; 
 struct pex_obj* pex_init (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 char* pex_run (struct pex_obj*,int,char const*,char* const*,char const*,char const*,int*) ; 

const char *
pex_one (int flags, const char *executable, char * const *argv,
	 const char *pname, const char *outname, const char *errname,
	 int *status, int *err)
{
  struct pex_obj *obj;
  const char *errmsg;

  obj = pex_init (0, pname, NULL);
  errmsg = pex_run (obj, flags, executable, argv, outname, errname, err);
  if (errmsg == NULL)
    {
      if (!pex_get_status (obj, 1, status))
	{
	  *err = 0;
	  errmsg = "pex_get_status failed";
	}
    }
  pex_free (obj);
  return errmsg;  
}