#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct stat {int dummy; } ;
struct TYPE_6__ {int flags; TYPE_1__* iovec; } ;
typedef  TYPE_2__ bfd ;
struct TYPE_5__ {int (* bstat ) (TYPE_2__*,struct stat*) ;} ;

/* Variables and functions */
 int BFD_IN_MEMORY ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  bfd_error_system_call ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_2__*,struct stat*) ; 

int
bfd_stat (bfd *abfd, struct stat *statbuf)
{
  int result;

  if ((abfd->flags & BFD_IN_MEMORY) != 0)
    abort ();

  if (abfd->iovec)
    result = abfd->iovec->bstat (abfd, statbuf);
  else
    result = -1;

  if (result < 0)
    bfd_set_error (bfd_error_system_call);
  return result;
}