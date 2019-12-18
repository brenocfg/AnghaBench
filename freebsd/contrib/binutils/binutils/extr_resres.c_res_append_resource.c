#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rc_res_resource ;
typedef  int /*<<< orphan*/  rc_res_id ;
struct TYPE_5__ {int /*<<< orphan*/ * res; TYPE_3__* dir; } ;
struct TYPE_6__ {int subdir; TYPE_1__ u; int /*<<< orphan*/  id; struct TYPE_6__* next; } ;
typedef  TYPE_2__ rc_res_entry ;
struct TYPE_7__ {unsigned long time; TYPE_2__* entries; scalar_t__ minor; scalar_t__ major; scalar_t__ characteristics; } ;
typedef  TYPE_3__ rc_res_directory ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 char* program_name ; 
 scalar_t__ res_alloc (int) ; 
 scalar_t__ res_id_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  res_ids_print (int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  stderr ; 
 unsigned long time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xexit (int) ; 

__attribute__((used)) static void
res_append_resource (rc_res_directory **resources, rc_res_resource *resource,
		     int cids, const rc_res_id *ids, int dupok)
{
  rc_res_entry *re = NULL;
  int i;

  assert (cids > 0);
  for (i = 0; i < cids; i++)
    {
      rc_res_entry **pp;

      if (*resources == NULL)
	{
	  static unsigned long timeval;

	  /* Use the same timestamp for every resource created in a
	     single run.  */
	  if (timeval == 0)
	    timeval = time (NULL);

	  *resources = ((rc_res_directory *)
			res_alloc (sizeof (rc_res_directory)));
	  (*resources)->characteristics = 0;
	  (*resources)->time = timeval;
	  (*resources)->major = 0;
	  (*resources)->minor = 0;
	  (*resources)->entries = NULL;
	}

      for (pp = &(*resources)->entries; *pp != NULL; pp = &(*pp)->next)
	if (res_id_cmp ((*pp)->id, ids[i]) == 0)
	  break;

      if (*pp != NULL)
	re = *pp;
      else
	{
	  re = (rc_res_entry *) res_alloc (sizeof (rc_res_entry));
	  re->next = NULL;
	  re->id = ids[i];
	  if ((i + 1) < cids)
	    {
	      re->subdir = 1;
	      re->u.dir = NULL;
	    }
	  else
	    {
	      re->subdir = 0;
	      re->u.res = NULL;
	    }

	  *pp = re;
	}

      if ((i + 1) < cids)
	{
	  if (! re->subdir)
	    {
	      fprintf (stderr, "%s: ", program_name);
	      res_ids_print (stderr, i, ids);
	      fprintf (stderr, ": expected to be a directory\n");
	      xexit (1);
	    }

	  resources = &re->u.dir;
	}
    }

  if (re->subdir)
    {
      fprintf (stderr, "%s: ", program_name);
      res_ids_print (stderr, cids, ids);
      fprintf (stderr, ": expected to be a leaf\n");
      xexit (1);
    }

  if (re->u.res != NULL)
    {
      if (dupok)
	return;

      fprintf (stderr, "%s: warning: ", program_name);
      res_ids_print (stderr, cids, ids);
      fprintf (stderr, ": duplicate value\n");
    }

  re->u.res = resource;
}