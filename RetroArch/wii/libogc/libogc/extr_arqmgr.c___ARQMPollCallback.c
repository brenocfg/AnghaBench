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
typedef  size_t u32 ;
struct TYPE_3__ {int /*<<< orphan*/  polled; int /*<<< orphan*/ * callback; int /*<<< orphan*/  arqhandle; } ;
typedef  int /*<<< orphan*/  ARQRequest ;
typedef  TYPE_1__ ARQM_Info ;

/* Variables and functions */
 size_t ARQM_STACKENTRIES ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* __ARQMInfo ; 

__attribute__((used)) static void __ARQMPollCallback(ARQRequest *req)
{
	u32 i;
	ARQM_Info *ptr = NULL;

	for(i=0;i<ARQM_STACKENTRIES;i++) {
		ptr = &__ARQMInfo[i];
		if(req==&ptr->arqhandle) break;
	}
	if(i>=ARQM_STACKENTRIES) return;

	ptr->callback = NULL;
	ptr->polled = TRUE;
}