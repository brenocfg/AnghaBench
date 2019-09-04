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
 int /*<<< orphan*/  ESgetpars ; 
 int MAXPARS ; 
 scalar_t__ gc_numpars ; 
 scalar_t__* gc_par ; 
 int /*<<< orphan*/  gc_putc_getpars (unsigned char) ; 
 int /*<<< orphan*/  gc_vt100state ; 

__attribute__((used)) static void 
gc_putc_square(unsigned char ch)
{
	int     i;

	for (i = 0; i < MAXPARS; i++) {
		gc_par[i] = 0;
	}

	gc_numpars = 0;
	gc_vt100state = ESgetpars;

	gc_putc_getpars(ch);

}