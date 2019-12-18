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
 char* strrchr (char const*,char) ; 

const char *get_filename_ext(const char *filename)
{
	const char *dot;

	dot = strrchr(filename, '.');
	if (!dot || dot == filename)
		return "";

	return dot + 1;
}