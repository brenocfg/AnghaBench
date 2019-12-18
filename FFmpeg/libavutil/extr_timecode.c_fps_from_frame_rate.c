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
struct TYPE_3__ {int den; int num; } ;
typedef  TYPE_1__ AVRational ;

/* Variables and functions */

__attribute__((used)) static int fps_from_frame_rate(AVRational rate)
{
    if (!rate.den || !rate.num)
        return -1;
    return (rate.num + rate.den/2) / rate.den;
}