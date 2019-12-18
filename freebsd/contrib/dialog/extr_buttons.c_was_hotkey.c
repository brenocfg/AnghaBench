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
 int FALSE ; 
 int TRUE ; 

__attribute__((used)) static int
was_hotkey(int this_key, int *used_keys, size_t next)
{
    int result = FALSE;

    if (next != 0) {
	size_t n;
	for (n = 0; n < next; ++n) {
	    if (used_keys[n] == this_key) {
		result = TRUE;
		break;
	    }
	}
    }
    return result;
}