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
 int /*<<< orphan*/ * af80_attrib ; 
 int /*<<< orphan*/ * af80_charset ; 
 int /*<<< orphan*/ * af80_rom ; 
 int /*<<< orphan*/ * af80_screen ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

void AF80_Exit(void)
{
	free(af80_screen);
	free(af80_attrib);
	free(af80_charset);
	free(af80_rom);
	af80_screen = af80_attrib = af80_charset = af80_rom = NULL;
}