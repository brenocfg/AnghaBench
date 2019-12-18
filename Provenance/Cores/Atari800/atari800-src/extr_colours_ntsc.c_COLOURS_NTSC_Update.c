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
struct TYPE_2__ {int hue; int /*<<< orphan*/  saturation; } ;

/* Variables and functions */
 TYPE_1__ COLOURS_NTSC_setup ; 
 int M_PI ; 
 int /*<<< orphan*/  UpdateYIQTable (double*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  YIQ2RGB (int*,double*) ; 
 int colorburst_angle ; 

void COLOURS_NTSC_Update(int colourtable[256])
{
	double yiq_table[768];
	UpdateYIQTable(yiq_table, - colorburst_angle + COLOURS_NTSC_setup.hue * M_PI, COLOURS_NTSC_setup.saturation);
	YIQ2RGB(colourtable, yiq_table);
}