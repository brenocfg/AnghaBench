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
 size_t bix ; 
 size_t filesize ; 
 size_t firstloc ; 
 scalar_t__* madr ; 
 scalar_t__ memcmp (scalar_t__*,scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__ num_matches ; 
 int /*<<< orphan*/  pat_len ; 
 scalar_t__* patterns ; 

void search_pattern (void)
{
	for (bix = 0; bix < filesize; bix++) {
		if (madr[bix] == patterns[0]) {
			if (memcmp (&madr[bix], patterns, pat_len) == 0) {
				if (num_matches == 0)
					firstloc = bix;
				num_matches++;
			}
		}
	}
}