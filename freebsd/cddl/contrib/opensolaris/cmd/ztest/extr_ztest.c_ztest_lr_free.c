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
 int strlen (char*) ; 
 int /*<<< orphan*/  umem_free (void*,size_t) ; 

void
ztest_lr_free(void *lr, size_t lrsize, char *name)
{
	size_t namesize = name ? strlen(name) + 1 : 0;

	umem_free(lr, lrsize + namesize);
}