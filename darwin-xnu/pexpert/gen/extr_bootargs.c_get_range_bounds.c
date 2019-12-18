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
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ NUM ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ getval (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  israngesep ; 

boolean_t
get_range_bounds(char *c, int64_t *lower, int64_t *upper)
{
	if (c == NULL || lower == NULL || upper == NULL) {
		return FALSE;
	}

	if (NUM != getval(c, lower, israngesep, TRUE)) {
		return FALSE;
	}

	while (*c != '\0') {
		if (*c == '_') {
			break;
		}
		c++;
	}

	if (*c == '_') {
		c++;
		if (NUM != getval(c, upper, israngesep, TRUE)) {
			return FALSE;
		}
	} else {
		return FALSE;
	}
	return TRUE;
}