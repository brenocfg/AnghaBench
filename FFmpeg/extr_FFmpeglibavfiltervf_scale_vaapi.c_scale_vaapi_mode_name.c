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
#define  VA_FILTER_SCALING_DEFAULT 131 
#define  VA_FILTER_SCALING_FAST 130 
#define  VA_FILTER_SCALING_HQ 129 
#define  VA_FILTER_SCALING_NL_ANAMORPHIC 128 

__attribute__((used)) static const char *scale_vaapi_mode_name(int mode)
{
    switch (mode) {
#define D(name) case VA_FILTER_SCALING_ ## name: return #name
        D(DEFAULT);
        D(FAST);
        D(HQ);
        D(NL_ANAMORPHIC);
#undef D
    default:
        return "Invalid";
    }
}