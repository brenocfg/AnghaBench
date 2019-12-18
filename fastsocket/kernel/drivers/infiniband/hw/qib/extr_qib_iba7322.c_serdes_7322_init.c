#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct qib_pportdata {TYPE_2__* dd; } ;
struct TYPE_4__ {TYPE_1__* cspec; } ;
struct TYPE_3__ {scalar_t__ r1; } ;

/* Variables and functions */
 int serdes_7322_init_new (struct qib_pportdata*) ; 
 int serdes_7322_init_old (struct qib_pportdata*) ; 

__attribute__((used)) static int serdes_7322_init(struct qib_pportdata *ppd)
{
	int ret = 0;
	if (ppd->dd->cspec->r1)
		ret = serdes_7322_init_old(ppd);
	else
		ret = serdes_7322_init_new(ppd);
	return ret;
}