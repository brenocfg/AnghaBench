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
 int av_hwdevice_iterate_types (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,int,int) ; 
 int /*<<< orphan*/  stderr ; 
 int test_device_type (int) ; 

int main(void)
{
    enum AVHWDeviceType type = AV_HWDEVICE_TYPE_NONE;
    int pass, fail, skip, err;

    pass = fail = skip = 0;
    while (1) {
        type = av_hwdevice_iterate_types(type);
        if (type == AV_HWDEVICE_TYPE_NONE)
            break;

        err = test_device_type(type);
        if (err == 0)
            ++pass;
        else if (err < 0)
            ++fail;
        else
            ++skip;
    }

    fprintf(stderr, "Attempted to test %d device types: "
            "%d passed, %d failed, %d skipped.\n",
            pass + fail + skip, pass, fail, skip);

    return fail > 0;
}