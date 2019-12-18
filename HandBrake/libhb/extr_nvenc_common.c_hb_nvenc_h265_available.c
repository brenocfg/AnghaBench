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

/* Variables and functions */
 int hb_check_nvenc_available () ; 

int hb_nvenc_h265_available()
{
    #if HB_PROJECT_FEATURE_NVENC
        return hb_check_nvenc_available();
    #else
        return 0;
    #endif
}