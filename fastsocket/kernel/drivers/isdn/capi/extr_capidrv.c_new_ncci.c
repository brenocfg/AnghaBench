#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_10__ {size_t chan; TYPE_3__* ncci_list; } ;
typedef  TYPE_2__ capidrv_plci ;
struct TYPE_11__ {size_t chan; struct TYPE_11__* next; scalar_t__ datahandle; TYPE_2__* plcip; int /*<<< orphan*/  state; int /*<<< orphan*/  ncci; } ;
typedef  TYPE_3__ capidrv_ncci ;
struct TYPE_12__ {TYPE_1__* bchans; } ;
typedef  TYPE_4__ capidrv_contr ;
struct TYPE_9__ {TYPE_3__* nccip; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  ST_NCCI_NONE ; 
 TYPE_3__* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline capidrv_ncci *new_ncci(capidrv_contr * card,
				     capidrv_plci * plcip,
				     u32 ncci)
{
	capidrv_ncci *nccip;

	nccip = kzalloc(sizeof(capidrv_ncci), GFP_ATOMIC);

	if (nccip == NULL)
		return NULL;

	nccip->ncci = ncci;
	nccip->state = ST_NCCI_NONE;
	nccip->plcip = plcip;
	nccip->chan = plcip->chan;
	nccip->datahandle = 0;

	nccip->next = plcip->ncci_list;
	plcip->ncci_list = nccip;

	card->bchans[plcip->chan].nccip = nccip;

	return nccip;
}