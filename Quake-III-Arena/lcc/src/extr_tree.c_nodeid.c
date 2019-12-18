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
typedef  scalar_t__ Tree ;
struct TYPE_2__ {scalar_t__ node; scalar_t__ printed; } ;

/* Variables and functions */
 TYPE_1__* ids ; 
 size_t nid ; 

int nodeid(Tree p) {
	int i = 1;

	ids[nid].node = p;
	while (ids[i].node != p)
		i++;
	if (i == nid)
		ids[nid++].printed = 0;
	return i;
}