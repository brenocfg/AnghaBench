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
typedef  int bfd_size_type ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_4__ {int /*<<< orphan*/ * the_bfd; } ;
typedef  TYPE_1__ asymbol ;

/* Variables and functions */
 TYPE_1__* bfd_zalloc (int /*<<< orphan*/ *,int) ; 

asymbol *
_bfd_generic_make_empty_symbol (bfd *abfd)
{
  bfd_size_type amt = sizeof (asymbol);
  asymbol *new = bfd_zalloc (abfd, amt);
  if (new)
    new->the_bfd = abfd;
  return new;
}