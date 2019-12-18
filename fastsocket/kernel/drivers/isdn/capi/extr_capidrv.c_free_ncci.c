#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct capidrv_ncci {size_t chan; struct capidrv_ncci* next; TYPE_1__* plcip; } ;
struct TYPE_7__ {TYPE_2__* bchans; } ;
typedef  TYPE_3__ capidrv_contr ;
struct TYPE_6__ {int /*<<< orphan*/ * nccip; } ;
struct TYPE_5__ {struct capidrv_ncci* ncci_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct capidrv_ncci*) ; 

__attribute__((used)) static void free_ncci(capidrv_contr * card, struct capidrv_ncci *nccip)
{
	struct capidrv_ncci **pp;

	for (pp = &(nccip->plcip->ncci_list); *pp; pp = &(*pp)->next) {
		if (*pp == nccip) {
			*pp = (*pp)->next;
			break;
		}
	}
	card->bchans[nccip->chan].nccip = NULL;
	kfree(nccip);
}