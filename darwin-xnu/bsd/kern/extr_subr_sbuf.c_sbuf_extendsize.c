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
 scalar_t__ SBUF_MAXEXTENDINCR ; 
 scalar_t__ SBUF_MAXEXTENDSIZE ; 
 int SBUF_MINEXTENDSIZE ; 

__attribute__((used)) static int
sbuf_extendsize(int size)
{
	int newsize;

	newsize = SBUF_MINEXTENDSIZE;
	while (newsize < size) {
		if (newsize < (int)SBUF_MAXEXTENDSIZE)
			newsize *= 2;
		else
			newsize += SBUF_MAXEXTENDINCR;
	}

	return (newsize);
}