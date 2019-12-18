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
struct TYPE_2__ {int driverId; } ;

/* Variables and functions */
 int ENODEV ; 
 int cinst ; 
 TYPE_1__** sc_adapter ; 

int get_card_from_id(int driver)
{
	int i;

	for(i = 0 ; i < cinst ; i++) {
		if(sc_adapter[i]->driverId == driver)
			return i;
	}
	return -ENODEV;
}