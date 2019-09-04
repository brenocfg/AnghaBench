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
typedef  int /*<<< orphan*/  buf ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  _mach_snprintf (char*,int,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf_stderr (char*,char const*,char*) ; 
 char* mach_error_string_int (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  mach_error_type (int /*<<< orphan*/ ) ; 

void
mach_error(const char *str, mach_error_t err)
{
	char *err_str;
	char buf[1024];
	boolean_t diag;

	err_str = mach_error_string_int(err, &diag);

	if (diag) {
		_mach_snprintf(buf, sizeof(buf), "%s %s (%x)", mach_error_type(err), err_str, err);
		err_str = buf;
	}

	fprintf_stderr("%s %s\n", str, err_str);
}