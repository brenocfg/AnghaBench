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
struct TYPE_6__ {int nb_index_tables; TYPE_1__* index_tables; } ;
struct TYPE_5__ {int index_sid; } ;
typedef  TYPE_1__ MXFIndexTable ;
typedef  TYPE_2__ MXFContext ;

/* Variables and functions */

__attribute__((used)) static MXFIndexTable *mxf_find_index_table(MXFContext *mxf, int index_sid)
{
    int i;
    for (i = 0; i < mxf->nb_index_tables; i++)
        if (mxf->index_tables[i].index_sid == index_sid)
            return &mxf->index_tables[i];
    return NULL;
}