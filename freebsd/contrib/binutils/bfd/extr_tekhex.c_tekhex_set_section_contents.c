#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* sec_ptr ;
typedef  int /*<<< orphan*/  file_ptr ;
typedef  int bfd_vma ;
typedef  int /*<<< orphan*/  bfd_size_type ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_10__ {TYPE_3__* sections; int /*<<< orphan*/  output_has_begun; } ;
typedef  TYPE_2__ bfd ;
struct TYPE_11__ {int flags; int vma; int size; struct TYPE_11__* next; } ;
typedef  TYPE_3__ asection ;
struct TYPE_9__ {int flags; } ;

/* Variables and functions */
 scalar_t__ CHUNK_MASK ; 
 int /*<<< orphan*/  FALSE ; 
 int SEC_ALLOC ; 
 int SEC_LOAD ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  find_chunk (TYPE_2__*,int) ; 
 int /*<<< orphan*/  move_section_contents (TYPE_2__*,TYPE_1__*,void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bfd_boolean
tekhex_set_section_contents (bfd *abfd,
			     sec_ptr section,
			     const void * locationp,
			     file_ptr offset,
			     bfd_size_type bytes_to_do)
{
  if (! abfd->output_has_begun)
    {
      /* The first time around, allocate enough sections to hold all the chunks.  */
      asection *s = abfd->sections;
      bfd_vma vma;

      for (s = abfd->sections; s; s = s->next)
	{
	  if (s->flags & SEC_LOAD)
	    {
	      for (vma = s->vma & ~(bfd_vma) CHUNK_MASK;
		   vma < s->vma + s->size;
		   vma += CHUNK_MASK)
		find_chunk (abfd, vma);
	    }
	}
    }

  if (section->flags & (SEC_LOAD | SEC_ALLOC))
    {
      move_section_contents (abfd, section, locationp, offset, bytes_to_do,
			     FALSE);
      return TRUE;
    }

  return FALSE;
}