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
 int ENODEV ; 
 scalar_t__ fb_get_options (char*,char**) ; 
 char* fb_mode ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static int imxfb_setup(void)
{
#ifndef MODULE
	char *opt, *options = NULL;

	if (fb_get_options("imxfb", &options))
		return -ENODEV;

	if (!options || !*options)
		return 0;

	while ((opt = strsep(&options, ",")) != NULL) {
		if (!*opt)
			continue;
		else
			fb_mode = opt;
	}
#endif
	return 0;
}