#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  enum AVCodecID { ____Placeholder_AVCodecID } AVCodecID ;
struct TYPE_2__ {int id; int index; } ;

/* Variables and functions */
 TYPE_1__* mxf_essence_mappings ; 

__attribute__((used)) static int mxf_get_essence_container_ul_index(enum AVCodecID id)
{
    int i;
    for (i = 0; mxf_essence_mappings[i].id; i++)
        if (mxf_essence_mappings[i].id == id)
            return mxf_essence_mappings[i].index;
    return -1;
}