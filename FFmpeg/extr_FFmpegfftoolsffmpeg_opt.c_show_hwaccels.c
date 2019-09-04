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
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 int AV_HWDEVICE_TYPE_NONE ; 
 char* av_hwdevice_get_type_name (int) ; 
 int av_hwdevice_iterate_types (int) ; 
 TYPE_1__* hwaccels ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static int show_hwaccels(void *optctx, const char *opt, const char *arg)
{
    enum AVHWDeviceType type = AV_HWDEVICE_TYPE_NONE;
    int i;

    printf("Hardware acceleration methods:\n");
    while ((type = av_hwdevice_iterate_types(type)) !=
           AV_HWDEVICE_TYPE_NONE)
        printf("%s\n", av_hwdevice_get_type_name(type));
    for (i = 0; hwaccels[i].name; i++)
        printf("%s\n", hwaccels[i].name);
    printf("\n");
    return 0;
}