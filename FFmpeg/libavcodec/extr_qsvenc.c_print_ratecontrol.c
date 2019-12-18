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
struct TYPE_3__ {scalar_t__ rc_mode; char const* name; } ;

/* Variables and functions */
 int FF_ARRAY_ELEMS (TYPE_1__*) ; 
 TYPE_1__* rc_names ; 

__attribute__((used)) static const char *print_ratecontrol(mfxU16 rc_mode)
{
    int i;
    for (i = 0; i < FF_ARRAY_ELEMS(rc_names); i++)
        if (rc_mode == rc_names[i].rc_mode)
            return rc_names[i].name;
    return "unknown";
}