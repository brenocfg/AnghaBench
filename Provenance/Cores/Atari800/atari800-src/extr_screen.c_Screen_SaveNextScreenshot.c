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
typedef  int /*<<< orphan*/  filename ;

/* Variables and functions */
 int FILENAME_MAX ; 
 int /*<<< orphan*/  Screen_FindScreenshotFilename (char*,int) ; 
 int /*<<< orphan*/  Screen_SaveScreenshot (char*,int) ; 

void Screen_SaveNextScreenshot(int interlaced)
{
	char filename[FILENAME_MAX];
	Screen_FindScreenshotFilename(filename, sizeof(filename));
	Screen_SaveScreenshot(filename, interlaced);
}