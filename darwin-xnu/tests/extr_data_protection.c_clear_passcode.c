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
 int set_passcode (int /*<<< orphan*/ *,char*) ; 

int
clear_passcode(char * passcode) {
	/*
	 * For the moment, this will set the passcode to the empty string
	 * (a known value); this will most likely need to change, or running
	 * this test may ruin everything™
	 */
	return set_passcode(NULL, passcode);
}