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
typedef  enum AVHWDeviceType { ____Placeholder_AVHWDeviceType } AVHWDeviceType ;
struct TYPE_2__ {int type; } ;

/* Variables and functions */
 int AV_HWDEVICE_TYPE_NONE ; 
 TYPE_1__** hw_table ; 

enum AVHWDeviceType av_hwdevice_iterate_types(enum AVHWDeviceType prev)
{
    enum AVHWDeviceType next;
    int i, set = 0;
    for (i = 0; hw_table[i]; i++) {
        if (prev != AV_HWDEVICE_TYPE_NONE && hw_table[i]->type <= prev)
            continue;
        if (!set || hw_table[i]->type < next) {
            next = hw_table[i]->type;
            set = 1;
        }
    }
    return set ? next : AV_HWDEVICE_TYPE_NONE;
}