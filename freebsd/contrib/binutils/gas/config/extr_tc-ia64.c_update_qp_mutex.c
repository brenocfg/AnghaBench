#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int valueT ;
struct TYPE_4__ {scalar_t__ path; scalar_t__ debug_dv; } ;
struct TYPE_3__ {int prmask; scalar_t__ path; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_qp_mutex (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 TYPE_2__ md ; 
 int /*<<< orphan*/  print_prmask (int) ; 
 TYPE_1__* qp_mutexes ; 
 int qp_mutexeslen ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
update_qp_mutex (valueT mask)
{
  int i;
  int add = 0;

  i = 0;
  while (i < qp_mutexeslen)
    {
      if ((qp_mutexes[i].prmask & mask) != 0)
	{
	  /* If it destroys and creates the same mutex, do nothing.  */
	  if (qp_mutexes[i].prmask == mask
	      && qp_mutexes[i].path == md.path)
	    {
	      i++;
	      add = -1;
	    }
	  else
	    {
	      int keep = 0;

	      if (md.debug_dv)
		{
		  fprintf (stderr, "  Clearing mutex relation");
		  print_prmask (qp_mutexes[i].prmask);
		  fprintf (stderr, "\n");
		}
	      
	      /* Deal with the old mutex with more than 3+ PRs only if
		 the new mutex on the same execution path with it.

		 FIXME: The 3+ mutex support is incomplete.
		 dot_pred_rel () may be a better place to fix it.  */
	      if (qp_mutexes[i].path == md.path)
		{
		  /* If it is a proper subset of the mutex, create a
		     new mutex.  */
		  if (add == 0
		      && (qp_mutexes[i].prmask & mask) == mask)
		    add = 1;
		  
		  qp_mutexes[i].prmask &= ~mask;
		  if (qp_mutexes[i].prmask & (qp_mutexes[i].prmask - 1))
		    {
		      /* Modify the mutex if there are more than one
			 PR left.  */
		      keep = 1;
		      i++;
		    }
		}
	      
	      if (keep == 0)
		/* Remove the mutex.  */
		qp_mutexes[i] = qp_mutexes[--qp_mutexeslen];
	    }
	}
      else
	++i;
    }

  if (add == 1)
    add_qp_mutex (mask);

  return add;
}