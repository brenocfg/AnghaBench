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
struct TYPE_5__ {struct TYPE_5__* archive_next; } ;
typedef  TYPE_1__ bfd ;
struct TYPE_6__ {TYPE_1__* archive_head; } ;

/* Variables and functions */
 TYPE_2__* obfd ; 

__attribute__((used)) static void
ar_addlib_doer (bfd *abfd, bfd *prev)
{
  /* Add this module to the output bfd.  */
  if (prev != NULL)
    prev->archive_next = abfd->archive_next;

  abfd->archive_next = obfd->archive_head;
  obfd->archive_head = abfd;
}