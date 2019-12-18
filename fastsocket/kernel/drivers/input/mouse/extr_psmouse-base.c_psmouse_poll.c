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
struct psmouse {int pktsize; int /*<<< orphan*/  packet; int /*<<< orphan*/  ps2dev; } ;

/* Variables and functions */
 int PSMOUSE_CMD_POLL ; 
 int ps2_command (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int psmouse_poll(struct psmouse *psmouse)
{
	return ps2_command(&psmouse->ps2dev, psmouse->packet,
			   PSMOUSE_CMD_POLL | (psmouse->pktsize << 8));
}