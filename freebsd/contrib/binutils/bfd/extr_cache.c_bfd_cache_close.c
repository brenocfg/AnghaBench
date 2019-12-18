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
struct TYPE_4__ {int /*<<< orphan*/ * iostream; int /*<<< orphan*/ * iovec; } ;
typedef  TYPE_1__ bfd ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bfd_cache_delete (TYPE_1__*) ; 
 int /*<<< orphan*/  cache_iovec ; 

bfd_boolean
bfd_cache_close (bfd *abfd)
{
  if (abfd->iovec != &cache_iovec)
    return TRUE;

  if (abfd->iostream == NULL)
    /* Previously closed.  */
    return TRUE;

  return bfd_cache_delete (abfd);
}