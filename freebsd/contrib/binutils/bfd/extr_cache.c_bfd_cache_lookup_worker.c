#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  enum cache_flag { ____Placeholder_cache_flag } cache_flag ;
struct TYPE_9__ {int flags; int /*<<< orphan*/ * iostream; int /*<<< orphan*/  where; struct TYPE_9__* my_archive; } ;
typedef  TYPE_1__ bfd ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int BFD_IN_MEMORY ; 
 int CACHE_NO_OPEN ; 
 int CACHE_NO_SEEK ; 
 int CACHE_NO_SEEK_ERROR ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  _bfd_error_handler (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  bfd_errmsg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_error_system_call ; 
 int /*<<< orphan*/  bfd_get_error () ; 
 TYPE_1__* bfd_last_cache ; 
 int /*<<< orphan*/ * bfd_open_file (TYPE_1__*) ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  insert (TYPE_1__*) ; 
 scalar_t__ real_fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snip (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static FILE *
bfd_cache_lookup_worker (bfd *abfd, enum cache_flag flag)
{
  bfd *orig_bfd = abfd;
  if ((abfd->flags & BFD_IN_MEMORY) != 0)
    abort ();

  if (abfd->my_archive)
    abfd = abfd->my_archive;

  if (abfd->iostream != NULL)
    {
      /* Move the file to the start of the cache.  */
      if (abfd != bfd_last_cache)
	{
	  snip (abfd);
	  insert (abfd);
	}
      return (FILE *) abfd->iostream;
    }

  if (flag & CACHE_NO_OPEN)
    return NULL;

  if (bfd_open_file (abfd) == NULL)
    ;
  else if (!(flag & CACHE_NO_SEEK)
	   && real_fseek ((FILE *) abfd->iostream, abfd->where, SEEK_SET) != 0
	   && !(flag & CACHE_NO_SEEK_ERROR))
    bfd_set_error (bfd_error_system_call);
  else
    return (FILE *) abfd->iostream;

  (*_bfd_error_handler) (_("reopening %B: %s\n"),
			 orig_bfd, bfd_errmsg (bfd_get_error ()));
  return NULL;
}