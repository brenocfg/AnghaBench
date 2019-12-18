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
typedef  int u32 ;
struct TYPE_2__ {int hres; int vres; int vmode_refresh; } ;

/* Variables and functions */
 int NUM_TOTAL_RES_MAP_REFRESH ; 
 int REFRESH_TOLERANCE ; 
 int abs (int) ; 
 TYPE_1__* res_map_refresh_tbl ; 

int viafb_get_refresh(int hres, int vres, u32 long_refresh)
{
#define REFRESH_TOLERANCE 3
	int i, nearest = -1, diff = REFRESH_TOLERANCE;
	for (i = 0; i < NUM_TOTAL_RES_MAP_REFRESH; i++) {
		if ((hres == res_map_refresh_tbl[i].hres)
		    && (vres == res_map_refresh_tbl[i].vres)
		    && (diff > (abs(long_refresh -
		    res_map_refresh_tbl[i].vmode_refresh)))) {
			diff = abs(long_refresh - res_map_refresh_tbl[i].
				vmode_refresh);
			nearest = i;
		}
	}
#undef REFRESH_TOLERANCE
	if (nearest > 0)
		return res_map_refresh_tbl[nearest].vmode_refresh;
	return 60;
}