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
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  prioritysort (int /*<<< orphan*/ *,int) ; 
 scalar_t__ unicode_combinable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void push(uint16_t ucs_ch, int *combcharcnt, uint16_t **ucsp)
{
	/*
	 * Make multiple combining character sequences canonical
	 */
	if (unicode_combinable(ucs_ch)) {
		++*combcharcnt;		/* start tracking a run */
	} else if (*combcharcnt) {
		if (*combcharcnt > 1) {
			prioritysort(*ucsp - *combcharcnt, *combcharcnt);
		}
		*combcharcnt = 0;	/* start over */
	}

	*(*ucsp)++ = ucs_ch;
}