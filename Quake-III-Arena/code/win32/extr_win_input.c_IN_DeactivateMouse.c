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
struct TYPE_2__ {scalar_t__ mouseActive; int /*<<< orphan*/  mouseInitialized; } ;

/* Variables and functions */
 int /*<<< orphan*/  IN_DeactivateDIMouse () ; 
 int /*<<< orphan*/  IN_DeactivateWin32Mouse () ; 
 scalar_t__ qfalse ; 
 TYPE_1__ s_wmv ; 

void IN_DeactivateMouse( void ) {
	if (!s_wmv.mouseInitialized ) {
		return;
	}
	if (!s_wmv.mouseActive ) {
		return;
	}
	s_wmv.mouseActive = qfalse;

	IN_DeactivateDIMouse();
	IN_DeactivateWin32Mouse();
}