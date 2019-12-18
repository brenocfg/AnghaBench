#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int cm_supported; int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/ * cm_getv ; 
 TYPE_1__* ehotk ; 
 int /*<<< orphan*/  pr_info (char*,char const*,int) ; 
 int /*<<< orphan*/  read_acpi_int (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void cmsg_quirk(int cm, const char *name)
{
	int dummy;

	/* Some BIOSes do not report cm although it is avaliable.
	   Check if cm_getv[cm] works and, if yes, assume cm should be set. */
	if (!(ehotk->cm_supported & (1 << cm))
	    && !read_acpi_int(ehotk->handle, cm_getv[cm], &dummy)) {
		pr_info("%s (%x) not reported by BIOS,"
			" enabling anyway\n", name, 1 << cm);
		ehotk->cm_supported |= 1 << cm;
	}
}