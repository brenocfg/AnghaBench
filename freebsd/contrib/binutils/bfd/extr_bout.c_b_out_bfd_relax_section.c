#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct bfd_link_info {int dummy; } ;
typedef  int /*<<< orphan*/  bfd_size_type ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_15__ {unsigned int size; int /*<<< orphan*/ * owner; } ;
typedef  TYPE_2__ asection ;
struct TYPE_16__ {TYPE_1__* howto; } ;
typedef  TYPE_3__ arelent ;
struct TYPE_14__ {int type; } ;

/* Variables and functions */
#define  ABS32CODE 130 
#define  ABS32CODE_SHRUNK 129 
#define  ALIGNER 128 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _bfd_generic_link_get_symbols (int /*<<< orphan*/ *) ; 
 unsigned int abs32code (int /*<<< orphan*/ *,TYPE_2__*,TYPE_3__*,unsigned int,struct bfd_link_info*) ; 
 unsigned int aligncode (int /*<<< orphan*/ *,TYPE_2__*,TYPE_3__*,unsigned int) ; 
 long bfd_canonicalize_reloc (int /*<<< orphan*/ *,TYPE_2__*,TYPE_3__**,int /*<<< orphan*/ ) ; 
 long bfd_get_reloc_upper_bound (int /*<<< orphan*/ *,TYPE_2__*) ; 
 TYPE_3__** bfd_malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_3__**) ; 

__attribute__((used)) static bfd_boolean
b_out_bfd_relax_section (bfd *abfd,
			 asection *i,
			 struct bfd_link_info *link_info,
			 bfd_boolean *again)
{
  /* Get enough memory to hold the stuff.  */
  bfd *input_bfd = i->owner;
  asection *input_section = i;
  unsigned int shrink = 0 ;
  arelent **reloc_vector = NULL;
  long reloc_size = bfd_get_reloc_upper_bound (input_bfd, input_section);

  if (reloc_size < 0)
    return FALSE;

  /* We only run this relaxation once.  It might work to run it
     multiple times, but it hasn't been tested.  */
  *again = FALSE;

  if (reloc_size)
    {
      long reloc_count;

      reloc_vector = bfd_malloc ((bfd_size_type) reloc_size);
      if (reloc_vector == NULL && reloc_size != 0)
	goto error_return;

      /* Get the relocs and think about them.  */
      reloc_count =
	bfd_canonicalize_reloc (input_bfd, input_section, reloc_vector,
				_bfd_generic_link_get_symbols (input_bfd));
      if (reloc_count < 0)
	goto error_return;
      if (reloc_count > 0)
	{
	  arelent **parent;

	  for (parent = reloc_vector; *parent; parent++)
	    {
	      arelent *r = *parent;

	      switch (r->howto->type)
		{
		case ALIGNER:
		  /* An alignment reloc.  */
		  shrink = aligncode (abfd, input_section, r, shrink);
		  break;
		case ABS32CODE:
		  /* A 32bit reloc in an addressing mode.  */
		  shrink = abs32code (input_bfd, input_section, r, shrink,
				      link_info);
		  break;
		case ABS32CODE_SHRUNK:
		  shrink += 4;
		  break;
		}
	    }
	}
    }
  input_section->size -= shrink;

  if (reloc_vector != NULL)
    free (reloc_vector);
  return TRUE;
 error_return:
  if (reloc_vector != NULL)
    free (reloc_vector);
  return FALSE;
}