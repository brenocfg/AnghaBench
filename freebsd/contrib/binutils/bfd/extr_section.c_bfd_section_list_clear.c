#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct bfd_hash_entry {int dummy; } ;
struct TYPE_4__ {int size; int /*<<< orphan*/  table; } ;
struct TYPE_5__ {TYPE_1__ section_htab; scalar_t__ section_count; int /*<<< orphan*/ * section_last; int /*<<< orphan*/ * sections; } ;
typedef  TYPE_2__ bfd ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
bfd_section_list_clear (bfd *abfd)
{
  abfd->sections = NULL;
  abfd->section_last = NULL;
  abfd->section_count = 0;
  memset (abfd->section_htab.table, 0,
	  abfd->section_htab.size * sizeof (struct bfd_hash_entry *));
}