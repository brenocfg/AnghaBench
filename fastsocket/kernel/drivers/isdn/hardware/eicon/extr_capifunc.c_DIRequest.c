#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  (* request ) (TYPE_3__*) ;} ;
struct TYPE_9__ {TYPE_1__ d; } ;
typedef  TYPE_2__ diva_card ;
typedef  size_t byte ;
struct TYPE_11__ {scalar_t__* FlowControlIdTable; int* FlowControlSkipTable; scalar_t__ os_card; } ;
struct TYPE_10__ {size_t ReqCh; scalar_t__ Id; scalar_t__ Req; scalar_t__* user; } ;
typedef  TYPE_3__ ENTITY ;
typedef  TYPE_4__ DIVA_CAPI_ADAPTER ;

/* Variables and functions */
 TYPE_4__* adapter ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 

__attribute__((used)) static void DIRequest(ENTITY * e)
{
	DIVA_CAPI_ADAPTER *a = &(adapter[(byte) e->user[0]]);
	diva_card *os_card = (diva_card *) a->os_card;

	if (e->Req && (a->FlowControlIdTable[e->ReqCh] == e->Id)) {
		a->FlowControlSkipTable[e->ReqCh] = 1;
	}

	(*(os_card->d.request)) (e);
}