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
struct TYPE_2__ {int /*<<< orphan*/  FileNameW; } ;
typedef  TYPE_1__ DIRENT ;

/* Variables and functions */
 int UniStrCmpi (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int CompareDirListByName(void *p1, void *p2)
{
	DIRENT *d1, *d2;
	if (p1 == NULL || p2 == NULL)
	{
		return 0;
	}
	d1 = *(DIRENT **)p1;
	d2 = *(DIRENT **)p2;
	if (d1 == NULL || d2 == NULL)
	{
		return 0;
	}
	return UniStrCmpi(d1->FileNameW, d2->FileNameW);
}