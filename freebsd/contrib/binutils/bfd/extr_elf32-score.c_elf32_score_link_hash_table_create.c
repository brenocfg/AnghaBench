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
struct bfd_link_hash_table {int dummy; } ;
struct TYPE_2__ {struct bfd_link_hash_table root; } ;
struct score_elf_link_hash_table {TYPE_1__ root; } ;
struct score_elf_link_hash_entry {int dummy; } ;
typedef  int bfd_size_type ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int /*<<< orphan*/  _bfd_elf_link_hash_table_init (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct score_elf_link_hash_table* bfd_malloc (int) ; 
 int /*<<< orphan*/  free (struct score_elf_link_hash_table*) ; 
 int /*<<< orphan*/  score_elf_link_hash_newfunc ; 

__attribute__((used)) static struct bfd_link_hash_table *
elf32_score_link_hash_table_create (bfd *abfd)
{
  struct score_elf_link_hash_table *ret;
  bfd_size_type amt = sizeof (struct score_elf_link_hash_table);

  ret = bfd_malloc (amt);
  if (ret == NULL)
    return NULL;

  if (!_bfd_elf_link_hash_table_init (&ret->root, abfd, score_elf_link_hash_newfunc,
				      sizeof (struct score_elf_link_hash_entry)))
    {
      free (ret);
      return NULL;
    }

  return &ret->root.root;
}