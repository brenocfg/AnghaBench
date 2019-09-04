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
struct TYPE_4__ {int /*<<< orphan*/  String; } ;
typedef  TYPE_1__ SL_UNICODE ;

/* Variables and functions */
 int /*<<< orphan*/  NdisFreeString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SlFree (TYPE_1__*) ; 

void SlFreeUnicode(SL_UNICODE *u)
{
	// Validate arguments
	if (u == NULL)
	{
		return;
	}

	// Release the string
	NdisFreeString(u->String);

	// Release the memory
	SlFree(u);
}