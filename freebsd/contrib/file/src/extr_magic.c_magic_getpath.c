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
 int FILE_LOAD ; 
 char const* MAGIC ; 
 char const* get_default_magic () ; 
 char* getenv (char*) ; 

const char *
magic_getpath(const char *magicfile, int action)
{
	if (magicfile != NULL)
		return magicfile;

	magicfile = getenv("MAGIC");
	if (magicfile != NULL)
		return magicfile;

	return action == FILE_LOAD ? get_default_magic() : MAGIC;
}