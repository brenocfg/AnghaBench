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
#define  FF_PROFILE_ARIB_PROFILE_A 129 
#define  FF_PROFILE_ARIB_PROFILE_C 128 

__attribute__((used)) static unsigned int get_profile_font_size(int profile)
{
    switch (profile) {
    case FF_PROFILE_ARIB_PROFILE_A:
        return 36;
    case FF_PROFILE_ARIB_PROFILE_C:
        return 18;
    default:
        return 0;
    }
}