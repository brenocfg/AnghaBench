#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
struct TYPE_4__ {int (* GetWidth ) (TYPE_1__*) ;} ;
typedef  TYPE_1__ CONSOLE ;

/* Variables and functions */
 int stub1 (TYPE_1__*) ; 

UINT GetConsoleWidth(CONSOLE *c)
{
	UINT size;

	size = c->GetWidth(c);

	if (size == 0)
	{
		size = 80;
	}

	if (size < 32)
	{
		size = 32;
	}

	if (size > 65536)
	{
		size = 65535;
	}

	return size;
}