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
struct substring {size_t length; size_t string; } ;

/* Variables and functions */
 int FALSE ; 
 scalar_t__ strncasecmp (size_t,size_t,size_t) ; 

__attribute__((used)) static bool
necp_check_suffix(struct substring parent, struct substring suffix, bool require_dot_before_suffix)
{
	if (parent.length <= suffix.length) {
		return (FALSE);
	}

	size_t length_difference = (parent.length - suffix.length);

	if (require_dot_before_suffix) {
		if (((char *)(parent.string + length_difference - 1))[0] != '.') {
			return (FALSE);
		}
	}

	// strncasecmp does case-insensitive check for all UTF-8 strings (ignores non-ASCII characters)
	return (strncasecmp(parent.string + length_difference, suffix.string, suffix.length) == 0);
}