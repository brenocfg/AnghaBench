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
typedef  scalar_t__ UINT ;
struct TYPE_2__ {int /*<<< orphan*/  ServerName; int /*<<< orphan*/  Path; } ;
typedef  TYPE_1__ LOG_FILE ;

/* Variables and functions */
 int StrCmpi (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int CmpLogFile(void *p1, void *p2)
{
	LOG_FILE *f1, *f2;
	UINT i;
	if (p1 == NULL || p2 == NULL)
	{
		return 0;
	}
	f1 = *(LOG_FILE **)p1;
	f2 = *(LOG_FILE **)p2;
	if (f1 == NULL || f2 == NULL)
	{
		return 0;
	}

	i = StrCmpi(f1->Path, f2->Path);
	if (i != 0)
	{
		return i;
	}

	return StrCmpi(f1->ServerName, f2->ServerName);
}