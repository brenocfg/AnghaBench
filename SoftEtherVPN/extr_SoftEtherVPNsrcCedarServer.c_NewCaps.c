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
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_4__ {int /*<<< orphan*/  Value; int /*<<< orphan*/  Name; } ;
typedef  TYPE_1__ CAPS ;

/* Variables and functions */
 int /*<<< orphan*/  CopyStr (char*) ; 
 TYPE_1__* ZeroMalloc (int) ; 

CAPS *NewCaps(char *name, UINT value)
{
	CAPS *c;
	// Validate arguments
	if (name == NULL)
	{
		return NULL;
	}

	c = ZeroMalloc(sizeof(CAPS));
	c->Name = CopyStr(name);
	c->Value = value;

	return c;
}