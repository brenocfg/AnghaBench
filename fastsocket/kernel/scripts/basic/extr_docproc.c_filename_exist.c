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
struct symfile {int /*<<< orphan*/  filename; } ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int symfilecnt ; 
 struct symfile* symfilelist ; 

__attribute__((used)) static struct symfile * filename_exist(char * filename)
{
	int i;
	for (i=0; i < symfilecnt; i++)
		if (strcmp(symfilelist[i].filename, filename) == 0)
			return &symfilelist[i];
	return NULL;
}