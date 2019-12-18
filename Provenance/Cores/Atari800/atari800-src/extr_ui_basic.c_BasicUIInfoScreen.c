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
 int /*<<< orphan*/  BasicUIMessage (char*,int) ; 
 int /*<<< orphan*/  Box (int,int,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  CenterPrint (int,int,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ClearScreen () ; 
 int /*<<< orphan*/  TitleScreen (char const*) ; 

__attribute__((used)) static void BasicUIInfoScreen(const char *title, const char *message)
{
	int y = 2;
	ClearScreen();
	TitleScreen(title);
	Box(0x9a, 0x94, 0, 1, 39, 23);
	while (*message != '\n') {
		CenterPrint(0x9a, 0x94, message, y++);
		while (*message++ != '\0');
	}
	BasicUIMessage("Press any key to continue", 1);
}