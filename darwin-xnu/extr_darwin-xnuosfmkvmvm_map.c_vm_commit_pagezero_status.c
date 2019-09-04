#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_map_t ;
struct TYPE_3__ {int /*<<< orphan*/  min_offset; int /*<<< orphan*/  pmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  pmap_advise_pagezero_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void vm_commit_pagezero_status(vm_map_t lmap) {
	pmap_advise_pagezero_range(lmap->pmap, lmap->min_offset);
}