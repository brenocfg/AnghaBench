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
struct TYPE_2__ {int value; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  Log_Write (char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* contentnames ; 

void PrintContents(int contents)
{
	int i;

	for (i = 0; contentnames[i].value; i++)
	{
		if (contents & contentnames[i].value)
		{
			Log_Write("%s,", contentnames[i].name);
		} //end if
	} //end for
}