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
 int sclp_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sclp_rw_event ; 

int
sclp_rw_init(void)
{
	static int init_done = 0;
	int rc;

	if (init_done)
		return 0;

	rc = sclp_register(&sclp_rw_event);
	if (rc == 0)
		init_done = 1;
	return rc;
}