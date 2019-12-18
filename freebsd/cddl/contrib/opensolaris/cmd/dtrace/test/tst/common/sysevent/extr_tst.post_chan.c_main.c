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
typedef  int /*<<< orphan*/  evchan_t ;

/* Variables and functions */
 int EVCH_CREAT ; 
 int EVCH_HOLD_PEND ; 
 int /*<<< orphan*/  EVCH_SLEEP ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ sysevent_evc_bind (char*,int /*<<< orphan*/ **,int) ; 
 scalar_t__ sysevent_evc_publish (int /*<<< orphan*/ *,char*,char*,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysevent_evc_unbind (int /*<<< orphan*/ *) ; 

int
main(int argc, char **argv)
{
	evchan_t *ch;

	if (sysevent_evc_bind("channel_dtest", &ch,
	    EVCH_CREAT | EVCH_HOLD_PEND) != 0) {
		(void) fprintf(stderr, "failed to bind to sysevent channel\n");
		return (1);
	}

	for (;;) {
		if (sysevent_evc_publish(ch, "class_dtest", "subclass_dtest",
		    "vendor_dtest", "publisher_dtest", NULL, EVCH_SLEEP) != 0) {
			(void) sysevent_evc_unbind(ch);
			(void) fprintf(stderr, "failed to publisth sysevent\n");
			return (1);
		}
		sleep(1);
	}
}