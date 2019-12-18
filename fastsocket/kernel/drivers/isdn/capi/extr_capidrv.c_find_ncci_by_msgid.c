#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_5__ {TYPE_2__* ncci_list; } ;
typedef  TYPE_1__ capidrv_plci ;
struct TYPE_6__ {scalar_t__ msgid; struct TYPE_6__* next; } ;
typedef  TYPE_2__ capidrv_ncci ;
typedef  int /*<<< orphan*/  capidrv_contr ;

/* Variables and functions */
 TYPE_1__* find_plci_by_ncci (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline capidrv_ncci *find_ncci_by_msgid(capidrv_contr * card,
					       u32 ncci, u16 msgid)
{
	capidrv_plci *plcip;
	capidrv_ncci *p;

	if ((plcip = find_plci_by_ncci(card, ncci)) == NULL)
		return NULL;

	for (p = plcip->ncci_list; p; p = p->next)
		if (p->msgid == msgid)
			return p;
	return NULL;
}