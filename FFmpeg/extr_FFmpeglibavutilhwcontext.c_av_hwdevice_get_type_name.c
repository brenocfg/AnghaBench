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
 int FF_ARRAY_ELEMS (char const**) ; 
 char const** hw_type_names ; 

const char *av_hwdevice_get_type_name(enum AVHWDeviceType type)
{
    if (type > AV_HWDEVICE_TYPE_NONE &&
        type < FF_ARRAY_ELEMS(hw_type_names))
        return hw_type_names[type];
    else
        return NULL;
}