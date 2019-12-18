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
struct TYPE_2__ {int* drvmap; int* chanmap; int /*<<< orphan*/ * usage; } ;

/* Variables and functions */
 int ISDN_MAX_CHANNELS ; 
 int /*<<< orphan*/  ISDN_USAGE_EXCLUSIVE ; 
 TYPE_1__* dev ; 
 int /*<<< orphan*/  isdn_info_update () ; 

void
isdn_unexclusive_channel(int di, int ch)
{
	int i;

	for (i = 0; i < ISDN_MAX_CHANNELS; i++)
		if ((dev->drvmap[i] == di) &&
		    (dev->chanmap[i] == ch)) {
			dev->usage[i] &= ~ISDN_USAGE_EXCLUSIVE;
			isdn_info_update();
			return;
		}
}