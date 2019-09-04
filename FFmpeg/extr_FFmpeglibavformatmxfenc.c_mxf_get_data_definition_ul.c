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
struct TYPE_4__ {int id; scalar_t__* uid; } ;
typedef  TYPE_1__ MXFCodecUL ;

/* Variables and functions */
 TYPE_1__* ff_mxf_data_definition_uls ; 

__attribute__((used)) static const MXFCodecUL *mxf_get_data_definition_ul(int type)
{
    const MXFCodecUL *uls = ff_mxf_data_definition_uls;
    while (uls->uid[0]) {
        if (type == uls->id)
            break;
        uls++;
    }
    return uls;
}