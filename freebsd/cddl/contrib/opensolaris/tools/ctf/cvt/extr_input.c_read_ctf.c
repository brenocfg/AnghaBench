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
typedef  int /*<<< orphan*/  read_cb_f ;

/* Variables and functions */
 int read_ctf_common (char*,char*,int /*<<< orphan*/ *,void*,int) ; 

int
read_ctf(char **files, int n, char *label, read_cb_f *func, void *private,
    int require_ctf)
{
	int found;
	int i, rc;

	for (i = 0, found = 0; i < n; i++) {
		if ((rc = read_ctf_common(files[i], label, func,
		    private, require_ctf)) < 0)
			return (rc);
		found += rc;
	}

	return (found);
}