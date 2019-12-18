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
 int /*<<< orphan*/  MAKE_PS2_CMD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char) ; 
 unsigned char TP_COMMAND ; 
 unsigned char TP_WRITE_MEM ; 
 scalar_t__ ps2_command (struct ps2dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int trackpoint_write(struct ps2dev *ps2dev, unsigned char loc, unsigned char val)
{
	if (ps2_command(ps2dev, NULL, MAKE_PS2_CMD(0, 0, TP_COMMAND)) ||
	    ps2_command(ps2dev, NULL, MAKE_PS2_CMD(0, 0, TP_WRITE_MEM)) ||
	    ps2_command(ps2dev, NULL, MAKE_PS2_CMD(0, 0, loc)) ||
	    ps2_command(ps2dev, NULL, MAKE_PS2_CMD(0, 0, val))) {
		return -1;
	}

	return 0;
}