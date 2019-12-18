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
 int bfin_probe_kernel_write (char*,char*,int) ; 

int kgdb_ebin2mem(char *buf, char *mem, int count)
{
	char *tmp_old, *tmp_new;
	int size;

	tmp_old = tmp_new = buf;

	for (size = 0; size < count; ++size) {
		if (*tmp_old == 0x7d)
			*tmp_new = *(++tmp_old) ^ 0x20;
		else
			*tmp_new = *tmp_old;
		tmp_new++;
		tmp_old++;
	}

	return bfin_probe_kernel_write(mem, buf, count);
}