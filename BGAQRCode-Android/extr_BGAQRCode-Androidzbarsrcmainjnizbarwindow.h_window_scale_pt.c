#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {long scale_num; long scale_den; } ;
typedef  TYPE_1__ zbar_window_t ;
struct TYPE_7__ {long x; long y; } ;
typedef  TYPE_2__ point_t ;

/* Variables and functions */

__attribute__((used)) static inline point_t window_scale_pt (zbar_window_t *w,
                                       point_t p)
{
    p.x = ((long)p.x * w->scale_num + w->scale_den - 1) / w->scale_den;
    p.y = ((long)p.y * w->scale_num + w->scale_den - 1) / w->scale_den;
    return(p);
}