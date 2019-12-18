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
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_3__ {int /*<<< orphan*/  nb_index_entries; int /*<<< orphan*/  index_entries; } ;
typedef  TYPE_1__ AVStream ;

/* Variables and functions */
 int ff_index_search_timestamp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int av_index_search_timestamp(AVStream *st, int64_t wanted_timestamp, int flags)
{
    return ff_index_search_timestamp(st->index_entries, st->nb_index_entries,
                                     wanted_timestamp, flags);
}