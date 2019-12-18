#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {void* debug_information_part; } ;
struct TYPE_17__ {TYPE_1__ r; } ;
struct TYPE_18__ {TYPE_2__ w; TYPE_4__* chain_root; } ;
typedef  TYPE_3__ ieee_data_type ;
typedef  void* file_ptr ;
struct TYPE_19__ {struct TYPE_19__* next; TYPE_5__* this; } ;
typedef  TYPE_4__ bfd_chain_type ;
typedef  scalar_t__ bfd_boolean ;
struct TYPE_20__ {TYPE_6__* sections; } ;
typedef  TYPE_5__ bfd ;
struct TYPE_21__ {int flags; scalar_t__ size; int /*<<< orphan*/  contents; struct TYPE_21__* next; } ;
typedef  TYPE_6__ asection ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 TYPE_3__* IEEE_DATA (TYPE_5__*) ; 
 int OBS ; 
 int SEC_DEBUGGING ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ TRUE ; 
 scalar_t__ bfd_bwrite (int /*<<< orphan*/ ,scalar_t__,TYPE_5__*) ; 
 scalar_t__ bfd_seek (TYPE_5__*,void*,int /*<<< orphan*/ ) ; 
 void* bfd_tell (TYPE_5__*) ; 
 int /*<<< orphan*/  flush () ; 
 TYPE_5__* output_bfd ; 
 unsigned char* output_ptr ; 
 unsigned char* output_ptr_end ; 
 unsigned char* output_ptr_start ; 
 int /*<<< orphan*/  relocate_debug (TYPE_5__*,TYPE_5__*) ; 

__attribute__((used)) static bfd_boolean
ieee_write_debug_part (bfd *abfd)
{
  ieee_data_type *ieee = IEEE_DATA (abfd);
  bfd_chain_type *chain = ieee->chain_root;
  unsigned char obuff[OBS];
  bfd_boolean some_debug = FALSE;
  file_ptr here = bfd_tell (abfd);

  output_ptr_start = output_ptr = obuff;
  output_ptr_end = obuff + OBS;
  output_ptr = obuff;
  output_bfd = abfd;

  if (chain == (bfd_chain_type *) NULL)
    {
      asection *s;

      for (s = abfd->sections; s != NULL; s = s->next)
	if ((s->flags & SEC_DEBUGGING) != 0)
	  break;
      if (s == NULL)
	{
	  ieee->w.r.debug_information_part = 0;
	  return TRUE;
	}

      ieee->w.r.debug_information_part = here;
      if (bfd_bwrite (s->contents, s->size, abfd) != s->size)
	return FALSE;
    }
  else
    {
      while (chain != (bfd_chain_type *) NULL)
	{
	  bfd *entry = chain->this;
	  ieee_data_type *entry_ieee = IEEE_DATA (entry);

	  if (entry_ieee->w.r.debug_information_part)
	    {
	      if (bfd_seek (entry, entry_ieee->w.r.debug_information_part,
			    SEEK_SET) != 0)
		return FALSE;
	      relocate_debug (abfd, entry);
	    }

	  chain = chain->next;
	}

      if (some_debug)
	ieee->w.r.debug_information_part = here;
      else
	ieee->w.r.debug_information_part = 0;

      flush ();
    }

  return TRUE;
}