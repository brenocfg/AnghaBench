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
 int /*<<< orphan*/  BUNYAN_FAKE_LOG_DEBUG (char*) ; 
 int /*<<< orphan*/  FMT ; 
 int /*<<< orphan*/  asprintf (char**,int /*<<< orphan*/ ,double,int,char*,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ waiting (int volatile*) ; 

int
main(int argc, char **argv)
{
	volatile int a = 0;
	int idx;
	double size = 250.5;

	while (waiting(&a) == 0)
		continue;

	for (idx = 0; idx < 10; idx++) {
		char *odd, *even, *json, *action;

		size *= 1.78;
		odd = idx % 2 == 1 ? "true" : "false";
		even = idx % 2 == 0 ? "true" : "false";
		action = idx == 7 ? "ignore" : "print";

		asprintf(&json, FMT, size, idx, odd, even, action);
		BUNYAN_FAKE_LOG_DEBUG(json);
		free(json);
	}

	BUNYAN_FAKE_LOG_DEBUG("{\"finished\": true}");

	return (0);
}