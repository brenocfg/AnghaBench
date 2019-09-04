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
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  error ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*,int) ; 

boolean_t
check_kr(int kr, char *fn) {
	if (kr) {
		sprintf(error, "%s() returned %d", fn, kr);
		return FALSE;
	}
	return TRUE;
}