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
typedef  int /*<<< orphan*/  cl_device_id ;

/* Variables and functions */
 int /*<<< orphan*/  CL_DEVICE_EXTENSIONS ; 
 int /*<<< orphan*/  av_free (char*) ; 
 char* opencl_get_device_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strstr (char*,char const*) ; 

__attribute__((used)) static int opencl_check_device_extension(cl_device_id device_id,
                                         const char *name)
{
    char *str;
    int found = 0;
    str = opencl_get_device_string(device_id,
                                   CL_DEVICE_EXTENSIONS);
    if (str && strstr(str, name))
        found = 1;
    av_free(str);
    return found;
}