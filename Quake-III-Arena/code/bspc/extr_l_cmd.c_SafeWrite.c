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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  Error (char*) ; 
 size_t fwrite (void*,int,int,int /*<<< orphan*/ *) ; 

void SafeWrite (FILE *f, void *buffer, int count)
{
	if (fwrite (buffer, 1, count, f) != (size_t)count)
		Error ("File write failure");
}