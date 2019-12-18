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
struct TYPE_5__ {TYPE_1__* scr; } ;
typedef  TYPE_2__ sync_common_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_4__ {int /*<<< orphan*/  scr_offset; } ;

/* Variables and functions */
 int SCR_HASH_SZ ; 

__attribute__((used)) static void scrSlip( sync_common_t * common, int64_t delta )
{
    int ii;
    for (ii = 0; ii < SCR_HASH_SZ; ii++)
    {
        common->scr[ii].scr_offset += delta;
    }
}