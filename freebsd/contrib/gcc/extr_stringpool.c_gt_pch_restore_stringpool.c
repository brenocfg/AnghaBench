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
struct TYPE_2__ {int /*<<< orphan*/  nelements; int /*<<< orphan*/  nslots; int /*<<< orphan*/  entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  ht_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ident_hash ; 
 TYPE_1__* spd ; 

void
gt_pch_restore_stringpool (void)
{
  ht_load (ident_hash, spd->entries, spd->nslots, spd->nelements, false);
  spd = NULL;
}