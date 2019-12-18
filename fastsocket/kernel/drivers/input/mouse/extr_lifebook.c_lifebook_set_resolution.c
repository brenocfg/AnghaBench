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
struct psmouse {int resolution; int /*<<< orphan*/  ps2dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PSMOUSE_CMD_SETRES ; 
 int /*<<< orphan*/  ps2_command (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lifebook_set_resolution(struct psmouse *psmouse, unsigned int resolution)
{
	static const unsigned char params[] = { 0, 1, 2, 2, 3 };
	unsigned char p;

	if (resolution == 0 || resolution > 400)
		resolution = 400;

	p = params[resolution / 100];
	ps2_command(&psmouse->ps2dev, &p, PSMOUSE_CMD_SETRES);
	psmouse->resolution = 50 << p;
}