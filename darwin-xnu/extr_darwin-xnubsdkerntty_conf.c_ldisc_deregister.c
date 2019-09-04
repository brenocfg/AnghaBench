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
 int LOADABLE_LDISC ; 
 int MAXLDISC ; 
 int /*<<< orphan*/ * linesw ; 
 int /*<<< orphan*/  nodisc ; 

void
ldisc_deregister(int discipline)
{
	if (discipline >= LOADABLE_LDISC && discipline < MAXLDISC) {
		linesw[discipline] = nodisc;
	}
}