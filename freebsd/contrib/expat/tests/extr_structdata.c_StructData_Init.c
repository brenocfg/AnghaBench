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
struct TYPE_3__ {int /*<<< orphan*/ * entries; scalar_t__ max_count; scalar_t__ count; } ;
typedef  TYPE_1__ StructData ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

void
StructData_Init(StructData *storage)
{
    assert(storage != NULL);
    storage->count = 0;
    storage->max_count = 0;
    storage->entries = NULL;
}