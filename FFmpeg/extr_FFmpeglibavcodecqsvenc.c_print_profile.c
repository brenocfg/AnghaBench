#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ mfxU16 ;
struct TYPE_3__ {scalar_t__ profile; char const* name; } ;

/* Variables and functions */
 int FF_ARRAY_ELEMS (TYPE_1__*) ; 
 TYPE_1__* profile_names ; 

__attribute__((used)) static const char *print_profile(mfxU16 profile)
{
    int i;
    for (i = 0; i < FF_ARRAY_ELEMS(profile_names); i++)
        if (profile == profile_names[i].profile)
            return profile_names[i].name;
    return "unknown";
}