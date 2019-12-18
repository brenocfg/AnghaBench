#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  DSPbase; } ;
typedef  TYPE_1__ IXJ ;

/* Variables and functions */
 int IXJMAX ; 
 TYPE_1__* ixj ; 

__attribute__((used)) static IXJ *ixj_alloc(void)
{
	int cnt;
	for(cnt=0; cnt<IXJMAX; cnt++) {
		if(!ixj[cnt].DSPbase)
			return &ixj[cnt];
	}
	return NULL;
}