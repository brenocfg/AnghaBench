#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int depth; int /*<<< orphan*/ * index; } ;
typedef  TYPE_1__ hb_preset_index_t ;

/* Variables and functions */
 int HB_MAX_PRESET_FOLDER_DEPTH ; 

void hb_preset_index_append(hb_preset_index_t *dst,
                            const hb_preset_index_t *src)
{
    int ii;
    for (ii = 0; ii < src->depth &&
                 dst->depth < HB_MAX_PRESET_FOLDER_DEPTH; ii++, dst->depth++)
    {
        dst->index[dst->depth] = src->index[ii];
    }
}