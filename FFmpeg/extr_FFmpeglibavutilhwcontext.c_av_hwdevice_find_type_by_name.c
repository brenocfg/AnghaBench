#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  enum AVHWDeviceType { ____Placeholder_AVHWDeviceType } AVHWDeviceType ;

/* Variables and functions */
 int AV_HWDEVICE_TYPE_NONE ; 
 int FF_ARRAY_ELEMS (scalar_t__*) ; 
 scalar_t__* hw_type_names ; 
 int /*<<< orphan*/  strcmp (scalar_t__,char const*) ; 

enum AVHWDeviceType av_hwdevice_find_type_by_name(const char *name)
{
    int type;
    for (type = 0; type < FF_ARRAY_ELEMS(hw_type_names); type++) {
        if (hw_type_names[type] && !strcmp(hw_type_names[type], name))
            return type;
    }
    return AV_HWDEVICE_TYPE_NONE;
}