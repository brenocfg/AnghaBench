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
 int /*<<< orphan*/  Limit (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAXOUT ; 
 int /*<<< orphan*/  MINOUT ; 

void mix_32_to_16_mono(short *dest, int *src, int count)
{
	int l;

	for (; count > 0; count--)
	{
		l = *dest;
		l += *src++;
		Limit( l, MAXOUT, MINOUT );
		*dest++ = l;
	}
}