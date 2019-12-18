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
 scalar_t__* filenames ; 
 int /*<<< orphan*/  free (void*) ; 
 size_t n_filenames ; 

__attribute__((used)) static void FilenamesFree(void)
{
	while (n_filenames > 0)
		free((void *) filenames[--n_filenames]);
	free((void *) filenames);
}