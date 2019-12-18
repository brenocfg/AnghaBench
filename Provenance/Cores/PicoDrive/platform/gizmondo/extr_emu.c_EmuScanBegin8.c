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
 scalar_t__ HighCol ; 
 scalar_t__ gfx_buffer ; 

__attribute__((used)) static int EmuScanBegin8(unsigned int num)
{
	// draw like the fast renderer
	HighCol = gfx_buffer + 328 * num;

	return 0;
}