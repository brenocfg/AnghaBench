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
struct elfcopy {int /*<<< orphan*/  abi; } ;
struct TYPE_2__ {int /*<<< orphan*/  abi; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,char const*) ; 
 TYPE_1__* osabis ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static void
set_osabi(struct elfcopy *ecp, const char *abi)
{
	int i, found;

	found = 0;
	for (i = 0; osabis[i].name != NULL; i++)
		if (strcasecmp(osabis[i].name, abi) == 0) {
			ecp->abi = osabis[i].abi;
			found = 1;
			break;
		}
	if (!found)
		errx(EXIT_FAILURE, "unrecognized OSABI %s", abi);
}