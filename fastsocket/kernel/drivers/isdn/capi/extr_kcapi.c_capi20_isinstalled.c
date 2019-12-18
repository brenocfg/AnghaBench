#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {scalar_t__ cardstate; } ;

/* Variables and functions */
 int CAPI_MAXCONTR ; 
 int /*<<< orphan*/  CAPI_NOERROR ; 
 int /*<<< orphan*/  CAPI_REGNOTINSTALLED ; 
 scalar_t__ CARD_RUNNING ; 
 TYPE_1__** capi_cards ; 

u16 capi20_isinstalled(void)
{
	int i;
	for (i = 0; i < CAPI_MAXCONTR; i++) {
		if (capi_cards[i] && capi_cards[i]->cardstate == CARD_RUNNING)
			return CAPI_NOERROR;
	}
	return CAPI_REGNOTINSTALLED;
}