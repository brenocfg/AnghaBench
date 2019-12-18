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
typedef  int uint8_t ;

/* Variables and functions */

__attribute__((used)) static int extract_component(int yo0, int yo1, int code)
{
    int yo;

    if (yo0 == yo1) {
        yo = yo0;
    } else if (code == 0) {
        yo = yo0;
    } else if (code == 1) {
        yo = yo1;
    } else {
        if (yo0 > yo1) {
            yo = (uint8_t) (((8 - code) * yo0 +
                             (code - 1) * yo1) / 7);
        } else {
            if (code == 6) {
                yo = 0;
            } else if (code == 7) {
                yo = 255;
            } else {
                yo = (uint8_t) (((6 - code) * yo0 +
                                 (code - 1) * yo1) / 5);
            }
        }
    }

    return yo;
}