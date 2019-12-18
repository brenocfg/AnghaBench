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
 char* av_hwdevice_get_type_name (int) ; 
 int av_hwdevice_iterate_types (int) ; 
 int /*<<< orphan*/  exit_program (int /*<<< orphan*/ ) ; 
 int hw_device_init_from_string (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int opt_init_hw_device(void *optctx, const char *opt, const char *arg)
{
    if (!strcmp(arg, "list")) {
        enum AVHWDeviceType type = AV_HWDEVICE_TYPE_NONE;
        printf("Supported hardware device types:\n");
        while ((type = av_hwdevice_iterate_types(type)) !=
               AV_HWDEVICE_TYPE_NONE)
            printf("%s\n", av_hwdevice_get_type_name(type));
        printf("\n");
        exit_program(0);
    } else {
        return hw_device_init_from_string(arg, NULL);
    }
}