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
 int /*<<< orphan*/  errbuf ; 
 int errflag ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,void*) ; 

__attribute__((used)) static int invalid_dso_handle(void *h)
{
	snprintf(errbuf, sizeof errbuf, "Invalid library handle %p", (void *)h);
	errflag = 1;
	return 1;
}