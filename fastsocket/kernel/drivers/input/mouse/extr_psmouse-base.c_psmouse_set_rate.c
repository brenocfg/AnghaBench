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
struct psmouse {unsigned char rate; int /*<<< orphan*/  ps2dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PSMOUSE_CMD_SETRATE ; 
 int /*<<< orphan*/  ps2_command (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void psmouse_set_rate(struct psmouse *psmouse, unsigned int rate)
{
	static const unsigned char rates[] = { 200, 100, 80, 60, 40, 20, 10, 0 };
	unsigned char r;
	int i = 0;

	while (rates[i] > rate) i++;
	r = rates[i];
	ps2_command(&psmouse->ps2dev, &r, PSMOUSE_CMD_SETRATE);
	psmouse->rate = r;
}