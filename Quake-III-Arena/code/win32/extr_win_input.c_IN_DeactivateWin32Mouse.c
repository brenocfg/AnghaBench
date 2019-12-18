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
 int /*<<< orphan*/  ClipCursor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseCapture () ; 
 scalar_t__ ShowCursor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

void IN_DeactivateWin32Mouse( void ) 
{
	ClipCursor (NULL);
	ReleaseCapture ();
	while (ShowCursor (TRUE) < 0)
		;
}