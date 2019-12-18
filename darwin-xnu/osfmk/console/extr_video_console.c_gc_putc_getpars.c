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
 int /*<<< orphan*/  ESask ; 
 int /*<<< orphan*/  ESgotpars ; 
 int /*<<< orphan*/  ESnormal ; 
 int MAXPARS ; 
 int gc_numpars ; 
 int* gc_par ; 
 int /*<<< orphan*/  gc_putc_gotpars (unsigned char) ; 
 int /*<<< orphan*/  gc_vt100state ; 

__attribute__((used)) static void 
gc_putc_getpars(unsigned char ch)
{
	if (ch == '?') {
		gc_vt100state = ESask;
		return;
	}
	if (ch == '[') {
		gc_vt100state = ESnormal;
		/* Not supported */
		return;
	}
	if (ch == ';' && gc_numpars < MAXPARS - 1) {
		gc_numpars++;
	} else
		if (ch >= '0' && ch <= '9') {
			gc_par[gc_numpars] *= 10;
			gc_par[gc_numpars] += ch - '0';
		} else {
			gc_numpars++;
			gc_vt100state = ESgotpars;
			gc_putc_gotpars(ch);
		}
}