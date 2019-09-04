#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* region_list; } ;
struct TYPE_5__ {int id; struct TYPE_5__* next; } ;
typedef  TYPE_1__ DVBSubRegion ;
typedef  TYPE_2__ DVBSubContext ;

/* Variables and functions */

__attribute__((used)) static DVBSubRegion* get_region(DVBSubContext *ctx, int region_id)
{
    DVBSubRegion *ptr = ctx->region_list;

    while (ptr && ptr->id != region_id) {
        ptr = ptr->next;
    }

    return ptr;
}