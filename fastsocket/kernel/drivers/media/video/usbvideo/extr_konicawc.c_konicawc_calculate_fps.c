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
struct uvd {struct konicawc* user_data; } ;
struct konicawc {size_t size; size_t speed; } ;

/* Variables and functions */
 int** spd_to_fps ; 

__attribute__((used)) static int konicawc_calculate_fps(struct uvd *uvd)
{
	struct konicawc *cam = uvd->user_data;
	return spd_to_fps[cam->size][cam->speed]/3;
}