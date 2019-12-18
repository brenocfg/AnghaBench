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
struct psmouse {int dummy; } ;

/* Variables and functions */
 scalar_t__ trackpoint_start_protocol (struct psmouse*,int /*<<< orphan*/ *) ; 
 scalar_t__ trackpoint_sync (struct psmouse*) ; 

__attribute__((used)) static int trackpoint_reconnect(struct psmouse *psmouse)
{
	if (trackpoint_start_protocol(psmouse, NULL))
		return -1;

	if (trackpoint_sync(psmouse))
		return -1;

	return 0;
}