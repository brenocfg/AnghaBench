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
 int FILENAMES_INITIAL_SIZE ; 
 scalar_t__ Util_realloc (void*,int) ; 
 char const** filenames ; 
 int n_filenames ; 

__attribute__((used)) static void FilenamesAdd(const char *filename)
{
	if (n_filenames >= FILENAMES_INITIAL_SIZE && (n_filenames & (n_filenames - 1)) == 0) {
		/* n_filenames is a power of two: allocate twice as much */
		filenames = (const char **) Util_realloc((void *) filenames, 2 * n_filenames * sizeof(const char *));
	}
	filenames[n_filenames++] = filename;
}