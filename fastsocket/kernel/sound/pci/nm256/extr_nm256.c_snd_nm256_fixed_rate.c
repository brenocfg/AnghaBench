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
 unsigned int ARRAY_SIZE (unsigned int*) ; 
 unsigned int* samplerates ; 
 int /*<<< orphan*/  snd_BUG () ; 

__attribute__((used)) static int
snd_nm256_fixed_rate(unsigned int rate)
{
	unsigned int i;
	for (i = 0; i < ARRAY_SIZE(samplerates); i++) {
		if (rate == samplerates[i])
			return i;
	}
	snd_BUG();
	return 0;
}