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
typedef  int /*<<< orphan*/  U32 ;
struct TYPE_2__ {int /*<<< orphan*/  DisabledEvents; } ;

/* Variables and functions */
 TYPE_1__ _SYSVIEW_Globals ; 

void SEGGER_SYSVIEW_DisableEvents(U32 DisableMask) {
  _SYSVIEW_Globals.DisabledEvents |= DisableMask;
}