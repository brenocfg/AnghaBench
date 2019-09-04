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
typedef  int /*<<< orphan*/  spnav_event ;
typedef  int /*<<< orphan*/  XEvent ;

/* Variables and functions */
 int /*<<< orphan*/  fgInitialiseSpaceball () ; 
 int /*<<< orphan*/  sball_initialized ; 
 int spnav_x11_event (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

int fgIsSpaceballXEvent(const XEvent *xev)
{
    spnav_event sev;

    if(!sball_initialized) {
        fgInitialiseSpaceball();
        if(!sball_initialized) {
            return 0;
        }
    }

    return spnav_x11_event(xev, &sev);
}