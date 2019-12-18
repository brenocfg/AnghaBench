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
struct TYPE_2__ {scalar_t__ skill; int /*<<< orphan*/  filename; } ;

/* Variables and functions */
 int MAX_CLIENTS ; 
 TYPE_1__** botcharacters ; 
 double fabs (scalar_t__) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

int BotFindCachedCharacter(char *charfile, float skill)
{
	int handle;

	for (handle = 1; handle <= MAX_CLIENTS; handle++)
	{
		if ( !botcharacters[handle] ) continue;
		if ( strcmp( botcharacters[handle]->filename, charfile ) == 0 &&
			(skill < 0 || fabs(botcharacters[handle]->skill - skill) < 0.01) )
		{
			return handle;
		} //end if
	} //end for
	return 0;
}