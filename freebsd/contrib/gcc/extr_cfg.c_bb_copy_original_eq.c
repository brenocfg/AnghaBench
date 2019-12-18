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
struct htab_bb_copy_original_entry {scalar_t__ index1; } ;

/* Variables and functions */

__attribute__((used)) static int
bb_copy_original_eq (const void *p, const void *q)
{
  struct htab_bb_copy_original_entry *data
    = ((struct htab_bb_copy_original_entry *)p);
  struct htab_bb_copy_original_entry *data2
    = ((struct htab_bb_copy_original_entry *)q);

  return data->index1 == data2->index1;
}