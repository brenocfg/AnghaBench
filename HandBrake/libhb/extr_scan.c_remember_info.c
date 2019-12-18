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
struct TYPE_3__ {int count; int /*<<< orphan*/  info; } ;
typedef  TYPE_1__ info_list_t ;
typedef  int /*<<< orphan*/  hb_work_info_t ;

/* Variables and functions */
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void remember_info( info_list_t *info_list, hb_work_info_t *info )
{
    for ( ; info_list->count; ++info_list )
    {
        if ( memcmp( &info_list->info, info, sizeof(*info) ) == 0 )
        {
            // we found a match - bump its count
            ++info_list->count;
            return;
        }
    }
    // no match found - add new entry to list (info_list points to
    // the first free slot). NB - we assume that info_list was allocated
    // so that it's big enough even if there are no dups. I.e., 10 slots
    // allocated if there are 10 previews.
    info_list->count = 1;
    info_list->info = *info;
}