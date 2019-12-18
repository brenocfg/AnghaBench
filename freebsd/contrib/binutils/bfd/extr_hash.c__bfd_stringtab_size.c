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
struct bfd_strtab_hash {int /*<<< orphan*/  size; } ;
typedef  int /*<<< orphan*/  bfd_size_type ;

/* Variables and functions */

bfd_size_type
_bfd_stringtab_size (struct bfd_strtab_hash *tab)
{
  return tab->size;
}