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
typedef  scalar_t__ int64_t ;
struct TYPE_5__ {int partitions_count; TYPE_1__* partitions; } ;
struct TYPE_4__ {int body_sid; scalar_t__ essence_length; scalar_t__ essence_offset; } ;
typedef  TYPE_1__ MXFPartition ;
typedef  TYPE_2__ MXFContext ;

/* Variables and functions */

__attribute__((used)) static int64_t mxf_essence_container_end(MXFContext *mxf, int body_sid)
{
    for (int x = mxf->partitions_count - 1; x >= 0; x--) {
        MXFPartition *p = &mxf->partitions[x];

        if (p->body_sid != body_sid)
            continue;

        if (!p->essence_length)
            return 0;

        return p->essence_offset + p->essence_length;
    }

    return 0;
}