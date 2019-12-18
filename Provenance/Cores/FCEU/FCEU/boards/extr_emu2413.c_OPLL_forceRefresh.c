#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int int32 ;
struct TYPE_3__ {int /*<<< orphan*/ * slot; } ;
typedef  TYPE_1__ OPLL ;

/* Variables and functions */
 int /*<<< orphan*/  UPDATE_EG (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UPDATE_PG (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UPDATE_RKS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UPDATE_TLL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UPDATE_WF (int /*<<< orphan*/ *) ; 

void OPLL_forceRefresh(OPLL * opll) {
	int32 i;

	if (opll == NULL)
		return;

	for (i = 0; i < 12; i++) {
		UPDATE_PG(&opll->slot[i]);
		UPDATE_RKS(&opll->slot[i]);
		UPDATE_TLL(&opll->slot[i]);
		UPDATE_WF(&opll->slot[i]);
		UPDATE_EG(&opll->slot[i]);
	}
}