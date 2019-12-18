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
struct TYPE_2__ {scalar_t__ address; scalar_t__ addend; scalar_t__ h; } ;
struct score_got_entry {scalar_t__ abfd; scalar_t__ symndx; TYPE_1__ d; } ;

/* Variables and functions */

__attribute__((used)) static int
score_elf_got_entry_eq (const void *entry1, const void *entry2)
{
  const struct score_got_entry *e1 = (struct score_got_entry *)entry1;
  const struct score_got_entry *e2 = (struct score_got_entry *)entry2;

  return e1->abfd == e2->abfd && e1->symndx == e2->symndx
    && (! e1->abfd ? e1->d.address == e2->d.address
	: e1->symndx >= 0 ? e1->d.addend == e2->d.addend
	: e1->d.h == e2->d.h);
}