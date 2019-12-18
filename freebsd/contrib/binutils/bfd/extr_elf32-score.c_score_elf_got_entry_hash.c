#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ address; } ;
struct score_got_entry {TYPE_2__* abfd; TYPE_1__ d; scalar_t__ symndx; } ;
typedef  scalar_t__ hashval_t ;
struct TYPE_4__ {scalar_t__ id; } ;

/* Variables and functions */

__attribute__((used)) static hashval_t
score_elf_got_entry_hash (const void *entry_)
{
  const struct score_got_entry *entry = (struct score_got_entry *)entry_;

  return entry->symndx
    + (!entry->abfd ? entry->d.address : entry->abfd->id);
}