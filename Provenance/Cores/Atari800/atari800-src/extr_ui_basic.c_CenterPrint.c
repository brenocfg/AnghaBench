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
 int /*<<< orphan*/  Print (int,int,char const*,int,int,int) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void CenterPrint(int fg, int bg, const char *string, int y)
{
	int length = strlen(string);
	Print(fg, bg, string, (length < 38) ? (40 - length) >> 1 : 1, y, 38);
}