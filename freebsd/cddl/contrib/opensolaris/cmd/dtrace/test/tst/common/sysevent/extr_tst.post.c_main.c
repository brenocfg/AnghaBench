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
typedef  int /*<<< orphan*/  sysevent_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ sysevent_post_event (char*,char*,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
main(int argc, char **argv)
{
	sysevent_id_t id;

	for (;;) {
		if (sysevent_post_event("class_dtest", "subclass_dtest",
		    "vendor_dtest", "publisher_dtest", NULL, &id) != 0) {
			(void) fprintf(stderr, "failed to post sysevent\n");
			return (1);
		}

		sleep(1);
	}
}