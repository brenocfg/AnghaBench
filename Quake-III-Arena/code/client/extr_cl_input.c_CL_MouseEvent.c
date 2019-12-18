#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int* mouseDx; size_t mouseIndex; int* mouseDy; } ;
struct TYPE_3__ {int keyCatchers; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_MOUSE_EVENT ; 
 int KEYCATCH_CGAME ; 
 int KEYCATCH_UI ; 
 int /*<<< orphan*/  UI_MOUSE_EVENT ; 
 int /*<<< orphan*/  VM_Call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cgvm ; 
 TYPE_2__ cl ; 
 TYPE_1__ cls ; 
 int /*<<< orphan*/  uivm ; 

void CL_MouseEvent( int dx, int dy, int time ) {
	if ( cls.keyCatchers & KEYCATCH_UI ) {
		VM_Call( uivm, UI_MOUSE_EVENT, dx, dy );
	} else if (cls.keyCatchers & KEYCATCH_CGAME) {
		VM_Call (cgvm, CG_MOUSE_EVENT, dx, dy);
	} else {
		cl.mouseDx[cl.mouseIndex] += dx;
		cl.mouseDy[cl.mouseIndex] += dy;
	}
}