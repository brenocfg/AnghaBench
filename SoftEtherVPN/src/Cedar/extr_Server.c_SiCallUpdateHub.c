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
struct TYPE_4__ {int Me; } ;
typedef  int /*<<< orphan*/  SERVER ;
typedef  int /*<<< orphan*/  PACK ;
typedef  int /*<<< orphan*/  HUB ;
typedef  TYPE_1__ FARM_MEMBER ;

/* Variables and functions */
 int /*<<< orphan*/  FreePack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewPack () ; 
 int /*<<< orphan*/ * SiCallTask (TYPE_1__*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SiPackAddCreateHub (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void SiCallUpdateHub(SERVER *s, FARM_MEMBER *f, HUB *h)
{
	PACK *p;
	// Validate arguments
	if (s == NULL || f == NULL)
	{
		return;
	}

	if (f->Me == false)
	{
		p = NewPack();

		SiPackAddCreateHub(p, h);

		p = SiCallTask(f, p, "updatehub");
		FreePack(p);
	}
}