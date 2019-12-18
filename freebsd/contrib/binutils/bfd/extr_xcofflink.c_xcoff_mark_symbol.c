#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_4__* section; } ;
struct TYPE_8__ {TYPE_1__ def; } ;
struct TYPE_9__ {scalar_t__ type; TYPE_2__ u; } ;
struct xcoff_link_hash_entry {int flags; TYPE_4__* toc_section; TYPE_3__ root; } ;
struct bfd_link_info {int dummy; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_10__ {int flags; } ;
typedef  TYPE_4__ asection ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int SEC_MARK ; 
 int /*<<< orphan*/  TRUE ; 
 int XCOFF_MARK ; 
 int /*<<< orphan*/  bfd_is_abs_section (TYPE_4__*) ; 
 scalar_t__ bfd_link_hash_defined ; 
 scalar_t__ bfd_link_hash_defweak ; 
 int /*<<< orphan*/  xcoff_mark (struct bfd_link_info*,TYPE_4__*) ; 

__attribute__((used)) static inline bfd_boolean
xcoff_mark_symbol (struct bfd_link_info *info, struct xcoff_link_hash_entry *h)
{
  if ((h->flags & XCOFF_MARK) != 0)
    return TRUE;

  h->flags |= XCOFF_MARK;
  if (h->root.type == bfd_link_hash_defined
      || h->root.type == bfd_link_hash_defweak)
    {
      asection *hsec;

      hsec = h->root.u.def.section;
      if (! bfd_is_abs_section (hsec)
	  && (hsec->flags & SEC_MARK) == 0)
	{
	  if (! xcoff_mark (info, hsec))
	    return FALSE;
	}
    }

  if (h->toc_section != NULL
      && (h->toc_section->flags & SEC_MARK) == 0)
    {
      if (! xcoff_mark (info, h->toc_section))
	return FALSE;
    }

  return TRUE;
}