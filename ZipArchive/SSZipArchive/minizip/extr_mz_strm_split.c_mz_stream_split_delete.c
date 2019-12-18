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
struct TYPE_3__ {struct TYPE_3__* path_disk; struct TYPE_3__* path_cd; } ;
typedef  TYPE_1__ mz_stream_split ;

/* Variables and functions */
 int /*<<< orphan*/  MZ_FREE (TYPE_1__*) ; 

void mz_stream_split_delete(void **stream)
{
    mz_stream_split *split = NULL;
    if (stream == NULL)
        return;
    split = (mz_stream_split *)*stream;
    if (split != NULL)
    {
        if (split->path_cd)
            MZ_FREE(split->path_cd);
        if (split->path_disk)
            MZ_FREE(split->path_disk);

        MZ_FREE(split);
    }
    *stream = NULL;
}