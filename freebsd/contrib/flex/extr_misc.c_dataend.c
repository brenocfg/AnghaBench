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
 int /*<<< orphan*/  dataflush () ; 
 scalar_t__ dataline ; 
 scalar_t__ datapos ; 
 scalar_t__ gentables ; 
 int /*<<< orphan*/  outn (char*) ; 

void dataend ()
{
	/* short circuit any output */
	if (gentables) {

		if (datapos > 0)
			dataflush ();

		/* add terminator for initialization; { for vi */
		outn ("    } ;\n");
	}
	dataline = 0;
	datapos = 0;
}