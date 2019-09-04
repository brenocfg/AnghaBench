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
struct TYPE_3__ {double volume; double attack; double decay; } ;
typedef  TYPE_1__ ChanParam ;

/* Variables and functions */

__attribute__((used)) static void update_volume(ChanParam *cp, double in)
{
    double delta = in - cp->volume;

    if (delta > 0.0)
        cp->volume += delta * cp->attack;
    else
        cp->volume += delta * cp->decay;
}