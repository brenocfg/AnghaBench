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
typedef  int /*<<< orphan*/  Nlist ;
typedef  int /*<<< orphan*/ ** Hideset ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/ *** hidesets ; 
 int nhidesets ; 

int
checkhideset(int hs, Nlist *np)
{
	Hideset hsp;

	if (hs>=nhidesets)
		abort();
	for (hsp = hidesets[hs]; *hsp; hsp++) {
		if (*hsp == np)
			return 1;
	}
	return 0;
}