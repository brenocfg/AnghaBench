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
 unsigned char* HighCol ; 
 scalar_t__ VRAM_CACHED_STUFF ; 
 int /*<<< orphan*/  dynamic_palette ; 

__attribute__((used)) static int EmuScanSlowBegin(unsigned int num)
{
	if (!dynamic_palette)
		HighCol = (unsigned char *)VRAM_CACHED_STUFF + num * 512 + 8;

	return 0;
}