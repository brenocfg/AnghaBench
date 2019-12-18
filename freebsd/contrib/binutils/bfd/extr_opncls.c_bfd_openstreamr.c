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
struct TYPE_7__ {char const* filename; int /*<<< orphan*/  direction; int /*<<< orphan*/ * iostream; } ;
typedef  TYPE_1__ bfd ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  _bfd_delete_bfd (TYPE_1__*) ; 
 TYPE_1__* _bfd_new_bfd () ; 
 int /*<<< orphan*/  bfd_cache_init (TYPE_1__*) ; 
 int /*<<< orphan*/ * bfd_find_target (char const*,TYPE_1__*) ; 
 int /*<<< orphan*/  read_direction ; 

bfd *
bfd_openstreamr (const char *filename, const char *target, void *streamarg)
{
  FILE *stream = streamarg;
  bfd *nbfd;
  const bfd_target *target_vec;

  nbfd = _bfd_new_bfd ();
  if (nbfd == NULL)
    return NULL;

  target_vec = bfd_find_target (target, nbfd);
  if (target_vec == NULL)
    {
      _bfd_delete_bfd (nbfd);
      return NULL;
    }

  nbfd->iostream = stream;
  nbfd->filename = filename;
  nbfd->direction = read_direction;

  if (! bfd_cache_init (nbfd))
    {
      _bfd_delete_bfd (nbfd);
      return NULL;
    }

  return nbfd;
}