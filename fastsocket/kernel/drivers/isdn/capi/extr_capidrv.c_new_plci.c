#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int chan; struct TYPE_8__* next; scalar_t__ msgid; scalar_t__ plci; int /*<<< orphan*/  state; } ;
typedef  TYPE_2__ capidrv_plci ;
struct TYPE_9__ {TYPE_1__* bchans; TYPE_2__* plci_list; } ;
typedef  TYPE_3__ capidrv_contr ;
struct TYPE_7__ {TYPE_2__* plcip; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  ST_PLCI_NONE ; 
 TYPE_2__* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static capidrv_plci *new_plci(capidrv_contr * card, int chan)
{
	capidrv_plci *plcip;

	plcip = kzalloc(sizeof(capidrv_plci), GFP_ATOMIC);

	if (plcip == NULL)
		return NULL;

	plcip->state = ST_PLCI_NONE;
	plcip->plci = 0;
	plcip->msgid = 0;
	plcip->chan = chan;
	plcip->next = card->plci_list;
	card->plci_list = plcip;
	card->bchans[chan].plcip = plcip;

	return plcip;
}