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
 int bufsize ; 
 int simple_rand () ; 

__attribute__((used)) static int rand_offs(void)
{
	int offs;

	if (bufsize < 32768)
		offs = simple_rand();
	else
		offs = (simple_rand() << 15) | simple_rand();
	offs %= bufsize;
	return offs;
}