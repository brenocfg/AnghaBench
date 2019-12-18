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
struct magic_set {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FILE_LOAD ; 
 int file_apprentice (struct magic_set*,char const*,int /*<<< orphan*/ ) ; 

int
magic_load(struct magic_set *ms, const char *magicfile)
{
	if (ms == NULL)
		return -1;
	return file_apprentice(ms, magicfile, FILE_LOAD);
}