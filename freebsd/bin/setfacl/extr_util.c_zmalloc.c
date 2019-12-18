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
 void* calloc (int,size_t) ; 
 int /*<<< orphan*/  err (int,char*) ; 

void *
zmalloc(size_t size)
{
	void *ptr;

	ptr = calloc(1, size);
	if (ptr == NULL)
		err(1, "calloc() failed");
	return (ptr);
}