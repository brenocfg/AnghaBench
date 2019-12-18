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
struct htab_bb_copy_original_entry {int /*<<< orphan*/  index1; } ;
typedef  int /*<<< orphan*/  hashval_t ;

/* Variables and functions */

__attribute__((used)) static hashval_t
bb_copy_original_hash (const void *p)
{
  struct htab_bb_copy_original_entry *data
    = ((struct htab_bb_copy_original_entry *)p);

  return data->index1;
}