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
typedef  int boolean_t ;
struct TYPE_2__ {unsigned int v_columns; } ;

/* Variables and functions */
 int FALSE ; 
 int* gc_buffer_tab_stops ; 
 TYPE_1__ vinfo ; 

__attribute__((used)) static boolean_t gc_is_tab_stop(unsigned int column)
{
	if (gc_buffer_tab_stops == NULL)
		return ((column % 8) == 0);
	if (column < vinfo.v_columns)
		return gc_buffer_tab_stops[column];
	else
		return FALSE;
}