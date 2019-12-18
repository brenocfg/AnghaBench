#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  onremove; int /*<<< orphan*/  oninsert; int /*<<< orphan*/  items; } ;
typedef  TYPE_1__ Ms ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 scalar_t__ ms_delete (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ms_init (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ms_clear(Ms *a)
{
    while (ms_delete(a, 0));
    free(a->items);
    ms_init(a, a->oninsert, a->onremove);
}