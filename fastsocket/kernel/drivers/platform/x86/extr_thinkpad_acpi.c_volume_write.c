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
typedef  int u8 ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int TP_CMOS_VOLUME_DOWN ; 
 int TP_CMOS_VOLUME_MUTE ; 
 int TP_CMOS_VOLUME_UP ; 
 int /*<<< orphan*/  acpi_ec_read (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  acpi_ec_write (int /*<<< orphan*/ ,int) ; 
 scalar_t__ issue_thinkpad_cmos_command (int) ; 
 char* next_cmd (char**) ; 
 int sscanf (char*,char*,int*) ; 
 scalar_t__ strlencmp (char*,char*) ; 
 int /*<<< orphan*/  volume_offset ; 

__attribute__((used)) static int volume_write(char *buf)
{
	int cmos_cmd, inc, i;
	u8 level, mute;
	int new_level, new_mute;
	char *cmd;

	while ((cmd = next_cmd(&buf))) {
		if (!acpi_ec_read(volume_offset, &level))
			return -EIO;
		new_mute = mute = level & 0x40;
		new_level = level = level & 0xf;

		if (strlencmp(cmd, "up") == 0) {
			if (mute)
				new_mute = 0;
			else
				new_level = level == 15 ? 15 : level + 1;
		} else if (strlencmp(cmd, "down") == 0) {
			if (mute)
				new_mute = 0;
			else
				new_level = level == 0 ? 0 : level - 1;
		} else if (sscanf(cmd, "level %d", &new_level) == 1 &&
			   new_level >= 0 && new_level <= 15) {
			/* new_level set */
		} else if (strlencmp(cmd, "mute") == 0) {
			new_mute = 0x40;
		} else
			return -EINVAL;

		if (new_level != level) {
			/* mute doesn't change */

			cmos_cmd = (new_level > level) ?
					TP_CMOS_VOLUME_UP : TP_CMOS_VOLUME_DOWN;
			inc = new_level > level ? 1 : -1;

			if (mute && (issue_thinkpad_cmos_command(cmos_cmd) ||
				     !acpi_ec_write(volume_offset, level)))
				return -EIO;

			for (i = level; i != new_level; i += inc)
				if (issue_thinkpad_cmos_command(cmos_cmd) ||
				    !acpi_ec_write(volume_offset, i + inc))
					return -EIO;

			if (mute &&
			    (issue_thinkpad_cmos_command(TP_CMOS_VOLUME_MUTE) ||
			     !acpi_ec_write(volume_offset, new_level + mute))) {
				return -EIO;
			}
		}

		if (new_mute != mute) {
			/* level doesn't change */

			cmos_cmd = (new_mute) ?
				   TP_CMOS_VOLUME_MUTE : TP_CMOS_VOLUME_UP;

			if (issue_thinkpad_cmos_command(cmos_cmd) ||
			    !acpi_ec_write(volume_offset, level + new_mute))
				return -EIO;
		}
	}

	return 0;
}