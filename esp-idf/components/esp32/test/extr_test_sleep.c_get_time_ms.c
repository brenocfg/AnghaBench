#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {float tv_sec; float tv_usec; } ;
struct TYPE_4__ {float tv_sec; float tv_usec; } ;

/* Variables and functions */
 float fabs (float) ; 
 int /*<<< orphan*/  gettimeofday (TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_2__ tv_start ; 
 TYPE_1__ tv_stop ; 

__attribute__((used)) static float get_time_ms(void)
{
    gettimeofday(&tv_stop, NULL);

    float dt = (tv_stop.tv_sec - tv_start.tv_sec) * 1e3f +
                (tv_stop.tv_usec - tv_start.tv_usec) * 1e-3f;
    return fabs(dt);
}