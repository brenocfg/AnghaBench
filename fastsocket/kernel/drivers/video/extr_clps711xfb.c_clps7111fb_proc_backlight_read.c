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
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int EDB_PD3_LCDBL ; 
 int EINVAL ; 
 int /*<<< orphan*/  PDDR ; 
 int clps_readb (int /*<<< orphan*/ ) ; 
 scalar_t__ machine_is_edb7211 () ; 
 int sprintf (char*,char*,int) ; 

__attribute__((used)) static int 
clps7111fb_proc_backlight_read(char *page, char **start, off_t off,
		int count, int *eof, void *data)
{
	/* We need at least two characters, one for the digit, and one for
	 * the terminating NULL. */
	if (count < 2) 
		return -EINVAL;

	if (machine_is_edb7211()) {
		return sprintf(page, "%d\n", 
				(clps_readb(PDDR) & EDB_PD3_LCDBL) ? 1 : 0);
	}

	return 0;
}