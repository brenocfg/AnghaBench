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
 int /*<<< orphan*/  CenterPrint (int,int,char const*,int) ; 
 int /*<<< orphan*/  ClearRectangle (int,int,int,int,int) ; 
 int /*<<< orphan*/  GetKeyPress () ; 
 int /*<<< orphan*/  PLATFORM_DisplayScreen () ; 

__attribute__((used)) static void BasicUIMessage(const char *msg, int waitforkey)
{
	ClearRectangle(0x94, 1, 22, 38, 22);
	CenterPrint(0x94, 0x9a, msg, 22);
	if (waitforkey)
		GetKeyPress();
	else
		PLATFORM_DisplayScreen();
}