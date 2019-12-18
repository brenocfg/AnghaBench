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
typedef  scalar_t__ Rune ;

/* Variables and functions */

Rune*
runestrchr(const Rune *s, Rune c)
{
	Rune c0 = c;
	Rune c1;

	if(c == 0) {
		while(*s++)
			;
		return (Rune*)s-1;
	}

	while((c1 = *s++))
		if(c1 == c0)
			return (Rune*)s-1;
	return 0;
}