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
typedef  int /*<<< orphan*/  UBYTE ;

/* Variables and functions */
 int /*<<< orphan*/  SMALLFONT_WIDTH ; 
 int /*<<< orphan*/  SmallFont_DrawChar (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static UBYTE *SmallFont_DrawInt(UBYTE *screen, int n, UBYTE color1, UBYTE color2)
{
	do {
		SmallFont_DrawChar(screen, n % 10, color1, color2);
		screen -= SMALLFONT_WIDTH;
		n /= 10;
	} while (n > 0);
	return screen;
}