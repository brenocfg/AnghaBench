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
 unsigned long EINVAL ; 
 scalar_t__ key_event_valid ; 
 int sscanf (char const*,char*,int*) ; 

__attribute__((used)) static unsigned long write_keys(const char *buffer, unsigned long count)
{
	int value;

	if (sscanf(buffer, " hotkey_ready : %i", &value) == 1 && value == 0) {
		key_event_valid = 0;
	} else {
		return -EINVAL;
	}

	return count;
}