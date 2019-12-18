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
typedef  int /*<<< orphan*/  mach_error_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 char* mach_error_string_int (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

char *
mach_error_string(mach_error_t err)
{
	boolean_t diag;

	return mach_error_string_int( err, &diag );
}