#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char const* filename; int /*<<< orphan*/  direction; int /*<<< orphan*/  xvec; } ;
typedef  TYPE_1__ bfd ;

/* Variables and functions */
 TYPE_1__* _bfd_new_bfd () ; 
 int /*<<< orphan*/  bfd_object ; 
 int /*<<< orphan*/  bfd_set_format (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  no_direction ; 

bfd *
bfd_create (const char *filename, bfd *templ)
{
  bfd *nbfd;

  nbfd = _bfd_new_bfd ();
  if (nbfd == NULL)
    return NULL;
  nbfd->filename = filename;
  if (templ)
    nbfd->xvec = templ->xvec;
  nbfd->direction = no_direction;
  bfd_set_format (nbfd, bfd_object);

  return nbfd;
}