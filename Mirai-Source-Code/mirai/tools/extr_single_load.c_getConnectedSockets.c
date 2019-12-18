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
struct TYPE_2__ {scalar_t__ slotUsed; } ;

/* Variables and functions */
 int maxFDSaw ; 
 TYPE_1__* stateTable ; 

int getConnectedSockets()
{
    int q = 0, i = 0;
    for(q = 0; q < maxFDSaw; q++) if(stateTable[q].slotUsed) i++;

    return i;
}