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

__attribute__((used)) static int rand_len(int offs)
{
	int len;

	if (bufsize < 32768)
		len = simple_rand();
	else
		len = (simple_rand() << 15) | simple_rand();
	len %= (bufsize - offs);
	return len;
}