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
struct TYPE_2__ {int* travelflagfortype; } ;

/* Variables and functions */
 int MAX_TRAVELTYPES ; 
 int TFL_INVALID ; 
 int TFL_NOTTEAM1 ; 
 int TFL_NOTTEAM2 ; 
 int TRAVELFLAG_NOTTEAM1 ; 
 int TRAVELFLAG_NOTTEAM2 ; 
 int TRAVELTYPE_MASK ; 
 TYPE_1__ aasworld ; 

__inline int AAS_TravelFlagForType_inline(int traveltype)
{
	int tfl;

	tfl = 0;
	if (tfl & TRAVELFLAG_NOTTEAM1)
		tfl |= TFL_NOTTEAM1;
	if (tfl & TRAVELFLAG_NOTTEAM2)
		tfl |= TFL_NOTTEAM2;
	traveltype &= TRAVELTYPE_MASK;
	if (traveltype < 0 || traveltype >= MAX_TRAVELTYPES)
		return TFL_INVALID;
	tfl |= aasworld.travelflagfortype[traveltype];
	return tfl;
}