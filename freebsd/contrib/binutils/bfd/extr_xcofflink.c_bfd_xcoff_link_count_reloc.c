#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct xcoff_link_hash_entry {int flags; } ;
struct bfd_link_info {int dummy; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_2__ {int /*<<< orphan*/  ldrel_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int XCOFF_LDREL ; 
 int XCOFF_REF_REGULAR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  _bfd_error_handler (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  bfd_error_no_symbols ; 
 scalar_t__ bfd_get_flavour (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 scalar_t__ bfd_target_xcoff_flavour ; 
 scalar_t__ bfd_wrapped_link_hash_lookup (int /*<<< orphan*/ *,struct bfd_link_info*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char const*) ; 
 TYPE_1__* xcoff_hash_table (struct bfd_link_info*) ; 
 int /*<<< orphan*/  xcoff_mark_symbol (struct bfd_link_info*,struct xcoff_link_hash_entry*) ; 

bfd_boolean
bfd_xcoff_link_count_reloc (bfd *output_bfd,
			    struct bfd_link_info *info,
			    const char *name)
{
  struct xcoff_link_hash_entry *h;

  if (bfd_get_flavour (output_bfd) != bfd_target_xcoff_flavour)
    return TRUE;

  h = ((struct xcoff_link_hash_entry *)
       bfd_wrapped_link_hash_lookup (output_bfd, info, name, FALSE, FALSE,
				     FALSE));
  if (h == NULL)
    {
      (*_bfd_error_handler) (_("%s: no such symbol"), name);
      bfd_set_error (bfd_error_no_symbols);
      return FALSE;
    }

  h->flags |= XCOFF_REF_REGULAR | XCOFF_LDREL;
  ++xcoff_hash_table (info)->ldrel_count;

  /* Mark the symbol to avoid garbage collection.  */
  if (! xcoff_mark_symbol (info, h))
    return FALSE;

  return TRUE;
}