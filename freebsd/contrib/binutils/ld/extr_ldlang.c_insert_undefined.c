#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * abfd; } ;
struct TYPE_5__ {TYPE_1__ undef; } ;
struct bfd_link_hash_entry {scalar_t__ type; TYPE_2__ u; } ;
struct TYPE_6__ {int /*<<< orphan*/  hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  bfd_link_add_undef (int /*<<< orphan*/ ,struct bfd_link_hash_entry*) ; 
 struct bfd_link_hash_entry* bfd_link_hash_lookup (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bfd_link_hash_new ; 
 scalar_t__ bfd_link_hash_undefined ; 
 int /*<<< orphan*/  einfo (int /*<<< orphan*/ ) ; 
 TYPE_3__ link_info ; 

__attribute__((used)) static void
insert_undefined (const char *name)
{
  struct bfd_link_hash_entry *h;

  h = bfd_link_hash_lookup (link_info.hash, name, TRUE, FALSE, TRUE);
  if (h == NULL)
    einfo (_("%P%F: bfd_link_hash_lookup failed: %E\n"));
  if (h->type == bfd_link_hash_new)
    {
      h->type = bfd_link_hash_undefined;
      h->u.undef.abfd = NULL;
      bfd_link_add_undef (link_info.hash, h);
    }
}