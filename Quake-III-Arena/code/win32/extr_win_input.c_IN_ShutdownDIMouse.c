#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  IDirectInputDevice_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirectInput_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_pMouse ; 
 int /*<<< orphan*/ * g_pdi ; 

void IN_ShutdownDIMouse( void ) {
    if (g_pMouse) {
		IDirectInputDevice_Release(g_pMouse);
		g_pMouse = NULL;
	}

    if (g_pdi) {
		IDirectInput_Release(g_pdi);
		g_pdi = NULL;
	}
}