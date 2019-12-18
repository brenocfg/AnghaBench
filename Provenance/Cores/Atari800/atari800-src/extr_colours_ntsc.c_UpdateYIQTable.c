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
struct TYPE_2__ {scalar_t__ loaded; } ;

/* Variables and functions */
 TYPE_1__ COLOURS_NTSC_external ; 
 int /*<<< orphan*/  UpdateYIQTableFromExternal (double*,double,double const) ; 
 int /*<<< orphan*/  UpdateYIQTableFromGenerated (double*,double,double const) ; 

__attribute__((used)) static void UpdateYIQTable(double yiq_table[768], double start_angle, const double start_saturation)
{
	if (COLOURS_NTSC_external.loaded)
		UpdateYIQTableFromExternal(yiq_table, start_angle, start_saturation);
	else
		UpdateYIQTableFromGenerated(yiq_table, start_angle, start_saturation);
}