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
 char* errmsg ; 
 scalar_t__ red ; 
 scalar_t__ strchr (char*,char) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

int
is_legal_filename(char *s)
{
	if (red && (*s == '!' || !strcmp(s, "..") || strchr(s, '/'))) {
		errmsg = "shell access restricted";
		return 0;
	}
	return 1;
}