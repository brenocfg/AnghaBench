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
struct TYPE_4__ {size_t* filter_idx; } ;
struct TYPE_5__ {TYPE_1__ fparam; int /*<<< orphan*/ * lpc_filter; } ;
typedef  TYPE_2__ DssSpContext ;

/* Variables and functions */
 int /*<<< orphan*/ ** dss_sp_filter_cb ; 

__attribute__((used)) static void dss_sp_unpack_filter(DssSpContext *p)
{
    int i;

    for (i = 0; i < 14; i++)
        p->lpc_filter[i] = dss_sp_filter_cb[i][p->fparam.filter_idx[i]];
}