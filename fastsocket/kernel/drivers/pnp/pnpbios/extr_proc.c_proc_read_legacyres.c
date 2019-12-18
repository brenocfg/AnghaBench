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
 int EIO ; 
 scalar_t__ pnp_bios_get_stat_res (char*) ; 

__attribute__((used)) static int proc_read_legacyres(char *buf, char **start, off_t pos,
			       int count, int *eof, void *data)
{
	/* Assume that the following won't overflow the buffer */
	if (pnp_bios_get_stat_res(buf))
		return -EIO;

	return count;		// FIXME: Return actual length
}