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
struct TYPE_3__ {scalar_t__ count; int /*<<< orphan*/  info; } ;
typedef  TYPE_1__ info_list_t ;
typedef  int /*<<< orphan*/  hb_work_info_t ;

/* Variables and functions */

__attribute__((used)) static void most_common_info( info_list_t *info_list, hb_work_info_t *info )
{
    int i, biggest = 0;
    for ( i = 1; info_list[i].count; ++i )
    {
        if ( info_list[i].count > info_list[biggest].count )
            biggest = i;
    }
    *info = info_list[biggest].info;
}