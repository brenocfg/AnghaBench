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
struct bfd_hash_table {int dummy; } ;
struct bfd_hash_entry {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * notice_hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * bfd_hash_lookup (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_hash_newfunc ; 
 int /*<<< orphan*/  bfd_hash_table_init_n (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  einfo (int /*<<< orphan*/ ) ; 
 TYPE_1__ link_info ; 
 int /*<<< orphan*/ * xmalloc (int) ; 

void
add_ysym (const char *name)
{
  if (link_info.notice_hash == NULL)
    {
      link_info.notice_hash = xmalloc (sizeof (struct bfd_hash_table));
      if (!bfd_hash_table_init_n (link_info.notice_hash,
				  bfd_hash_newfunc,
				  sizeof (struct bfd_hash_entry),
				  61))
	einfo (_("%P%F: bfd_hash_table_init failed: %E\n"));
    }

  if (bfd_hash_lookup (link_info.notice_hash, name, TRUE, TRUE) == NULL)
    einfo (_("%P%F: bfd_hash_lookup failed: %E\n"));
}