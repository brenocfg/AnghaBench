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
struct xcoff_link_size_list {int size; struct xcoff_link_hash_entry* h; struct xcoff_link_size_list* next; } ;
struct xcoff_link_hash_entry {int /*<<< orphan*/  flags; } ;
struct bfd_link_info {int dummy; } ;
struct bfd_link_hash_entry {int dummy; } ;
typedef  int bfd_size_type ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_2__ {struct xcoff_link_size_list* size_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  XCOFF_HAS_SIZE ; 
 struct xcoff_link_size_list* bfd_alloc (int /*<<< orphan*/ *,int) ; 
 scalar_t__ bfd_get_flavour (int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_target_xcoff_flavour ; 
 TYPE_1__* xcoff_hash_table (struct bfd_link_info*) ; 

bfd_boolean
bfd_xcoff_link_record_set (bfd *output_bfd,
			   struct bfd_link_info *info,
			   struct bfd_link_hash_entry *harg,
			   bfd_size_type size)
{
  struct xcoff_link_hash_entry *h = (struct xcoff_link_hash_entry *) harg;
  struct xcoff_link_size_list *n;
  bfd_size_type amt;

  if (bfd_get_flavour (output_bfd) != bfd_target_xcoff_flavour)
    return TRUE;

  /* This will hardly ever be called.  I don't want to burn four bytes
     per global symbol, so instead the size is kept on a linked list
     attached to the hash table.  */
  amt = sizeof (* n);
  n = bfd_alloc (output_bfd, amt);
  if (n == NULL)
    return FALSE;
  n->next = xcoff_hash_table (info)->size_list;
  n->h = h;
  n->size = size;
  xcoff_hash_table (info)->size_list = n;

  h->flags |= XCOFF_HAS_SIZE;

  return TRUE;
}