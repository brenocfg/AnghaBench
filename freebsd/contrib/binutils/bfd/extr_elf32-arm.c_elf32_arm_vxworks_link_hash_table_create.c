#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct elf32_arm_link_hash_table {int vxworks_p; scalar_t__ use_rel; } ;
struct bfd_link_hash_table {int dummy; } ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 struct bfd_link_hash_table* elf32_arm_link_hash_table_create (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct bfd_link_hash_table *
elf32_arm_vxworks_link_hash_table_create (bfd *abfd)
{
  struct bfd_link_hash_table *ret;

  ret = elf32_arm_link_hash_table_create (abfd);
  if (ret)
    {
      struct elf32_arm_link_hash_table *htab
	= (struct elf32_arm_link_hash_table *) ret;
      htab->use_rel = 0;
      htab->vxworks_p = 1;
    }
  return ret;
}