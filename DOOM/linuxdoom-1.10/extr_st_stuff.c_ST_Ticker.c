#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  health; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_Random () ; 
 int /*<<< orphan*/  ST_updateWidgets () ; 
 TYPE_1__* plyr ; 
 int /*<<< orphan*/  st_clock ; 
 int /*<<< orphan*/  st_oldhealth ; 
 int /*<<< orphan*/  st_randomnumber ; 

void ST_Ticker (void)
{

    st_clock++;
    st_randomnumber = M_Random();
    ST_updateWidgets();
    st_oldhealth = plyr->health;

}