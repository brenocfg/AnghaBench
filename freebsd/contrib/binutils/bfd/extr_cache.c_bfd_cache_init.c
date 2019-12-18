#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_4__ {int /*<<< orphan*/ * iovec; int /*<<< orphan*/ * iostream; } ;
typedef  TYPE_1__ bfd ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_ASSERT (int /*<<< orphan*/ ) ; 
 scalar_t__ BFD_CACHE_MAX_OPEN ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  cache_iovec ; 
 int /*<<< orphan*/  close_one () ; 
 int /*<<< orphan*/  insert (TYPE_1__*) ; 
 scalar_t__ open_files ; 

bfd_boolean
bfd_cache_init (bfd *abfd)
{
  BFD_ASSERT (abfd->iostream != NULL);
  if (open_files >= BFD_CACHE_MAX_OPEN)
    {
      if (! close_one ())
	return FALSE;
    }
  abfd->iovec = &cache_iovec;
  insert (abfd);
  ++open_files;
  return TRUE;
}