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
struct section_hash_entry {int dummy; } ;
struct TYPE_5__ {void* mtime_set; int /*<<< orphan*/  flags; void* cacheable; int /*<<< orphan*/ * usrdata; scalar_t__ section_count; void* output_has_begun; void* opened_once; scalar_t__ origin; int /*<<< orphan*/ * my_archive; int /*<<< orphan*/  format; int /*<<< orphan*/ * section_last; int /*<<< orphan*/ * sections; int /*<<< orphan*/  section_htab; scalar_t__ where; int /*<<< orphan*/ * iostream; int /*<<< orphan*/  direction; int /*<<< orphan*/ * arch_info; int /*<<< orphan*/ * memory; scalar_t__ id; } ;
typedef  TYPE_1__ bfd ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_NO_FLAGS ; 
 void* FALSE ; 
 int /*<<< orphan*/  _bfd_id_counter ; 
 int /*<<< orphan*/  bfd_default_arch_struct ; 
 int /*<<< orphan*/  bfd_error_no_memory ; 
 int /*<<< orphan*/  bfd_hash_table_init_n (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  bfd_section_hash_newfunc ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_unknown ; 
 TYPE_1__* bfd_zmalloc (int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  no_direction ; 
 int /*<<< orphan*/ * objalloc_create () ; 

bfd *
_bfd_new_bfd (void)
{
  bfd *nbfd;

  nbfd = bfd_zmalloc (sizeof (bfd));
  if (nbfd == NULL)
    return NULL;

  nbfd->id = _bfd_id_counter++;

  nbfd->memory = objalloc_create ();
  if (nbfd->memory == NULL)
    {
      bfd_set_error (bfd_error_no_memory);
      free (nbfd);
      return NULL;
    }

  nbfd->arch_info = &bfd_default_arch_struct;

  nbfd->direction = no_direction;
  nbfd->iostream = NULL;
  nbfd->where = 0;
  if (!bfd_hash_table_init_n (& nbfd->section_htab, bfd_section_hash_newfunc,
			      sizeof (struct section_hash_entry), 251))
    {
      free (nbfd);
      return NULL;
    }
  nbfd->sections = NULL;
  nbfd->section_last = NULL;
  nbfd->format = bfd_unknown;
  nbfd->my_archive = NULL;
  nbfd->origin = 0;
  nbfd->opened_once = FALSE;
  nbfd->output_has_begun = FALSE;
  nbfd->section_count = 0;
  nbfd->usrdata = NULL;
  nbfd->cacheable = FALSE;
  nbfd->flags = BFD_NO_FLAGS;
  nbfd->mtime_set = FALSE;

  return nbfd;
}