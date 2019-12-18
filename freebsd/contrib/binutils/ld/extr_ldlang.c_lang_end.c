#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* section; scalar_t__ value; } ;
struct TYPE_8__ {TYPE_2__ def; } ;
struct bfd_link_hash_entry {scalar_t__ type; TYPE_3__ u; } ;
typedef  scalar_t__ bfd_vma ;
typedef  scalar_t__ bfd_boolean ;
typedef  int /*<<< orphan*/  asection ;
struct TYPE_10__ {int /*<<< orphan*/ * name; } ;
struct TYPE_9__ {int /*<<< orphan*/  hash; scalar_t__ shared; scalar_t__ relocatable; } ;
struct TYPE_6__ {scalar_t__ output_offset; int /*<<< orphan*/ * output_section; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * bfd_get_section_by_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bfd_get_section_vma (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_link_hash_defined ; 
 scalar_t__ bfd_link_hash_defweak ; 
 struct bfd_link_hash_entry* bfd_link_hash_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ bfd_scan_vma (int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_set_start_address (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  einfo (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  entry_section ; 
 TYPE_5__ entry_symbol ; 
 int /*<<< orphan*/ * entry_symbol_default ; 
 TYPE_4__ link_info ; 
 int /*<<< orphan*/  output_bfd ; 

__attribute__((used)) static void
lang_end (void)
{
  struct bfd_link_hash_entry *h;
  bfd_boolean warn;

  if (link_info.relocatable || link_info.shared)
    warn = FALSE;
  else
    warn = TRUE;

  if (entry_symbol.name == NULL)
    {
      /* No entry has been specified.  Look for the default entry, but
	 don't warn if we don't find it.  */
      entry_symbol.name = entry_symbol_default;
      warn = FALSE;
    }

  h = bfd_link_hash_lookup (link_info.hash, entry_symbol.name,
			    FALSE, FALSE, TRUE);
  if (h != NULL
      && (h->type == bfd_link_hash_defined
	  || h->type == bfd_link_hash_defweak)
      && h->u.def.section->output_section != NULL)
    {
      bfd_vma val;

      val = (h->u.def.value
	     + bfd_get_section_vma (output_bfd,
				    h->u.def.section->output_section)
	     + h->u.def.section->output_offset);
      if (! bfd_set_start_address (output_bfd, val))
	einfo (_("%P%F:%s: can't set start address\n"), entry_symbol.name);
    }
  else
    {
      bfd_vma val;
      const char *send;

      /* We couldn't find the entry symbol.  Try parsing it as a
	 number.  */
      val = bfd_scan_vma (entry_symbol.name, &send, 0);
      if (*send == '\0')
	{
	  if (! bfd_set_start_address (output_bfd, val))
	    einfo (_("%P%F: can't set start address\n"));
	}
      else
	{
	  asection *ts;

	  /* Can't find the entry symbol, and it's not a number.  Use
	     the first address in the text section.  */
	  ts = bfd_get_section_by_name (output_bfd, entry_section);
	  if (ts != NULL)
	    {
	      if (warn)
		einfo (_("%P: warning: cannot find entry symbol %s;"
			 " defaulting to %V\n"),
		       entry_symbol.name,
		       bfd_get_section_vma (output_bfd, ts));
	      if (! bfd_set_start_address (output_bfd,
					   bfd_get_section_vma (output_bfd,
								ts)))
		einfo (_("%P%F: can't set start address\n"));
	    }
	  else
	    {
	      if (warn)
		einfo (_("%P: warning: cannot find entry symbol %s;"
			 " not setting start address\n"),
		       entry_symbol.name);
	    }
	}
    }

  /* Don't bfd_hash_table_free (&lang_definedness_table);
     map file output may result in a call of lang_track_definedness.  */
}