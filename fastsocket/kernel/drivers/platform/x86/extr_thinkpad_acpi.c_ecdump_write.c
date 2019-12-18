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
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  acpi_ec_write (int,int) ; 
 char* next_cmd (char**) ; 
 int sscanf (char*,char*,int*,int*) ; 

__attribute__((used)) static int ecdump_write(char *buf)
{
	char *cmd;
	int i, v;

	while ((cmd = next_cmd(&buf))) {
		if (sscanf(cmd, "0x%x 0x%x", &i, &v) == 2) {
			/* i and v set */
		} else if (sscanf(cmd, "0x%x %u", &i, &v) == 2) {
			/* i and v set */
		} else
			return -EINVAL;
		if (i >= 0 && i < 256 && v >= 0 && v < 256) {
			if (!acpi_ec_write(i, v))
				return -EIO;
		} else
			return -EINVAL;
	}

	return 0;
}