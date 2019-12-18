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
 int /*<<< orphan*/  DEFAULT_SCREENSHOT_FILENAME_FORMAT ; 
 int FILENAME_MAX ; 
 int /*<<< orphan*/  Log_print (char*) ; 
 char* screenshot_filename_format ; 
 int screenshot_no_max ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void Screen_SetScreenshotFilenamePattern(const char *p)
{
	char *f = screenshot_filename_format;
	char no_width = '0';
	screenshot_no_max = 1;
	/* 9 because sprintf'ed "no" can be 9 digits */
	while (f < screenshot_filename_format + FILENAME_MAX - 9) {
		/* replace a sequence of hashes with e.g. "%05d" */
		if (*p == '#') {
			if (no_width > '0') /* already seen a sequence of hashes */
				break;          /* invalid */
			/* count hashes */
			do {
				screenshot_no_max *= 10;
				p++;
				no_width++;
				/* now no_width is the number of hashes seen so far
				   and p points after the counted hashes */
			} while (no_width < '9' && *p == '#'); /* no more than 9 hashes */
			*f++ = '%';
			*f++ = '0';
			*f++ = no_width;
			*f++ = 'd';
			continue;
		}
		if (*p == '%')
			*f++ = '%'; /* double the percents */
		*f++ = *p;
		if (*p == '\0')
			return; /* ok */
		p++;
	}
	Log_print("Invalid filename pattern for screenshots, using default.");
	strcpy(screenshot_filename_format, DEFAULT_SCREENSHOT_FILENAME_FORMAT);
	screenshot_no_max = 1000;
}