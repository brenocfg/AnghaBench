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
typedef  int /*<<< orphan*/  TaskHandle_t ;
struct TYPE_3__ {int /*<<< orphan*/  xCoreID; } ;
typedef  TYPE_1__ TCB_t ;
typedef  int /*<<< orphan*/  BaseType_t ;

/* Variables and functions */
 TYPE_1__* prvGetTCBFromHandle (int /*<<< orphan*/ ) ; 

BaseType_t xTaskGetAffinity( TaskHandle_t xTask )
{
	TCB_t *pxTCB;

	pxTCB = prvGetTCBFromHandle( xTask );

	return pxTCB->xCoreID;
}