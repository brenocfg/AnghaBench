#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_5__ {scalar_t__ direction; int /*<<< orphan*/  mtime_set; scalar_t__ iostream; int /*<<< orphan*/  where; struct TYPE_5__* lru_prev; int /*<<< orphan*/  cacheable; } ;
typedef  TYPE_1__ bfd ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bfd_cache_delete (TYPE_1__*) ; 
 int /*<<< orphan*/  bfd_get_mtime (TYPE_1__*) ; 
 TYPE_1__* bfd_last_cache ; 
 scalar_t__ no_direction ; 
 scalar_t__ read_direction ; 
 int /*<<< orphan*/  real_ftell (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bfd_boolean
close_one (void)
{
  register bfd *kill;

  if (bfd_last_cache == NULL)
    kill = NULL;
  else
    {
      for (kill = bfd_last_cache->lru_prev;
	   ! kill->cacheable;
	   kill = kill->lru_prev)
	{
	  if (kill == bfd_last_cache)
	    {
	      kill = NULL;
	      break;
	    }
	}
    }

  if (kill == NULL)
    {
      /* There are no open cacheable BFD's.  */
      return TRUE;
    }

  kill->where = real_ftell ((FILE *) kill->iostream);

  /* Save the file st_mtime.  This is a hack so that gdb can detect when
     an executable has been deleted and recreated.  The only thing that
     makes this reasonable is that st_mtime doesn't change when a file
     is unlinked, so saving st_mtime makes BFD's file cache operation
     a little more transparent for this particular usage pattern.  If we
     hadn't closed the file then we would not have lost the original
     contents, st_mtime etc.  Of course, if something is writing to an
     existing file, then this is the wrong thing to do.
     FIXME: gdb should save these times itself on first opening a file,
     and this hack be removed.  */
  if (kill->direction == no_direction || kill->direction == read_direction)
    {
      bfd_get_mtime (kill);
      kill->mtime_set = TRUE;
    }

  return bfd_cache_delete (kill);
}