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
struct TYPE_6__ {int flags; TYPE_1__* iovec; } ;
typedef  TYPE_2__ bfd ;
struct TYPE_5__ {int (* bflush ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int BFD_IN_MEMORY ; 
 int stub1 (TYPE_2__*) ; 

int
bfd_flush (bfd *abfd)
{
  if ((abfd->flags & BFD_IN_MEMORY) != 0)
    return 0;

  if (abfd->iovec)
    return abfd->iovec->bflush (abfd);
  return 0;
}