#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  net_dev; } ;
typedef  TYPE_1__* PRTMP_ADAPTER ;
typedef  int INT ;

/* Variables and functions */
 int /*<<< orphan*/  VIRTUAL_IF_INC (TYPE_1__*) ; 
 scalar_t__ VIRTUAL_IF_NUM (TYPE_1__*) ; 
 scalar_t__ rt28xx_open (int /*<<< orphan*/ ) ; 

__inline INT VIRTUAL_IF_UP(PRTMP_ADAPTER pAd)
{
	if (VIRTUAL_IF_NUM(pAd) == 0)
	{
		if (rt28xx_open(pAd->net_dev) != 0)
			return -1;
	}
	else
	{
	}
	VIRTUAL_IF_INC(pAd);
	return 0;
}