#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bfd_target ;
struct TYPE_7__ {char const* filename; int /*<<< orphan*/  direction; } ;
typedef  TYPE_1__ bfd ;

/* Variables and functions */
 int /*<<< orphan*/  _bfd_delete_bfd (TYPE_1__*) ; 
 TYPE_1__* _bfd_new_bfd () ; 
 int /*<<< orphan*/  bfd_error_system_call ; 
 int /*<<< orphan*/ * bfd_find_target (char const*,TYPE_1__*) ; 
 int /*<<< orphan*/ * bfd_open_file (TYPE_1__*) ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_direction ; 

bfd *
bfd_openw (const char *filename, const char *target)
{
  bfd *nbfd;
  const bfd_target *target_vec;

  /* nbfd has to point to head of malloc'ed block so that bfd_close may
     reclaim it correctly.  */
  nbfd = _bfd_new_bfd ();
  if (nbfd == NULL)
    return NULL;

  target_vec = bfd_find_target (target, nbfd);
  if (target_vec == NULL)
    {
      _bfd_delete_bfd (nbfd);
      return NULL;
    }

  nbfd->filename = filename;
  nbfd->direction = write_direction;

  if (bfd_open_file (nbfd) == NULL)
    {
      /* File not writeable, etc.  */
      bfd_set_error (bfd_error_system_call);
      _bfd_delete_bfd (nbfd);
      return NULL;
  }

  return nbfd;
}