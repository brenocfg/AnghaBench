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
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 unsigned long SST_SIZE ; 

int sigorset(sigset_t *dest, const sigset_t *left, const sigset_t *right)
{
	unsigned long i = 0, *d = (void*) dest, *l = (void*) left, *r = (void*) right;
	for(; i < SST_SIZE; i++) d[i] = l[i] | r[i];
	return 0;
}