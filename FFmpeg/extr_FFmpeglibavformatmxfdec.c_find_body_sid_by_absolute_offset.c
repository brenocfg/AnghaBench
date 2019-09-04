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
struct TYPE_4__ {scalar_t__ pack_ofs; int body_sid; } ;
typedef  TYPE_2__ MXFContext ;

/* Variables and functions */

__attribute__((used)) static int find_body_sid_by_absolute_offset(MXFContext *mxf, int64_t offset)
{
    // we look for partition where the offset is placed
    int a, b, m;
    int64_t pack_ofs;

    a = -1;
    b = mxf->partitions_count;

    while (b - a > 1) {
        m = (a + b) >> 1;
        pack_ofs = mxf->partitions[m].pack_ofs;
        if (pack_ofs <= offset)
            a = m;
        else
            b = m;
    }

    if (a == -1)
        return 0;
    return mxf->partitions[a].body_sid;
}