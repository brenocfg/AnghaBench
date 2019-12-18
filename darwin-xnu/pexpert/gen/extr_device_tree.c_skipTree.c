#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned int nChildren; } ;
typedef  TYPE_1__* RealDTEntry ;

/* Variables and functions */
 TYPE_1__* skipProperties (TYPE_1__*) ; 

__attribute__((used)) static RealDTEntry
skipTree(RealDTEntry root)
{
	RealDTEntry entry;
	unsigned int k;

	entry = skipProperties(root);
	if (entry == NULL) {
		return NULL;
	}
	for (k = 0; k < root->nChildren; k++) {
		entry = skipTree(entry);
	}
	return entry;
}