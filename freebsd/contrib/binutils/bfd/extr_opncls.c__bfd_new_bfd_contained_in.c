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
struct TYPE_5__ {int /*<<< orphan*/  target_defaulted; int /*<<< orphan*/  direction; struct TYPE_5__* my_archive; int /*<<< orphan*/  iovec; int /*<<< orphan*/  xvec; } ;
typedef  TYPE_1__ bfd ;

/* Variables and functions */
 TYPE_1__* _bfd_new_bfd () ; 
 int /*<<< orphan*/  read_direction ; 

bfd *
_bfd_new_bfd_contained_in (bfd *obfd)
{
  bfd *nbfd;

  nbfd = _bfd_new_bfd ();
  if (nbfd == NULL)
    return NULL;
  nbfd->xvec = obfd->xvec;
  nbfd->iovec = obfd->iovec;
  nbfd->my_archive = obfd;
  nbfd->direction = read_direction;
  nbfd->target_defaulted = obfd->target_defaulted;
  return nbfd;
}