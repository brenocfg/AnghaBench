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
struct ps2dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAKE_PS2_CMD (int /*<<< orphan*/ ,int,unsigned char) ; 
 unsigned char TP_COMMAND ; 
 scalar_t__ ps2_command (struct ps2dev*,unsigned char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int trackpoint_read(struct ps2dev *ps2dev, unsigned char loc, unsigned char *results)
{
	if (ps2_command(ps2dev, NULL, MAKE_PS2_CMD(0, 0, TP_COMMAND)) ||
	    ps2_command(ps2dev, results, MAKE_PS2_CMD(0, 1, loc))) {
		return -1;
	}

	return 0;
}