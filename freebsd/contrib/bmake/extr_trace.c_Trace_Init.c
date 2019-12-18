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
 int /*<<< orphan*/  VAR_GLOBAL ; 
 int /*<<< orphan*/  Var_Value (char*,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  fopen (char const*,char*) ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  trfile ; 
 int /*<<< orphan*/  trpid ; 
 int /*<<< orphan*/  trwd ; 

void
Trace_Init(const char *pathname)
{
	char *p1;
	if (pathname != NULL) {
		trpid = getpid();
		trwd = Var_Value(".CURDIR", VAR_GLOBAL, &p1);

		trfile = fopen(pathname, "a");
	}
}