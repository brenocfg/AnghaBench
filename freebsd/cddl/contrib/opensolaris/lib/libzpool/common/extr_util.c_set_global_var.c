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
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ u_longlong_t ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENOTSUP ; 
 int EOVERFLOW ; 
 int /*<<< orphan*/  RTLD_LAZY ; 
 scalar_t__ UINT32_MAX ; 
 int /*<<< orphan*/  dlclose (void*) ; 
 void* dlopen (char*,int /*<<< orphan*/ ) ; 
 scalar_t__* dlsym (void*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 char* strchr (char*,char) ; 
 scalar_t__ strtoull (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
set_global_var(char *arg)
{
	void *zpoolhdl;
	char *varname = arg, *varval;
	u_longlong_t val;

#ifndef _LITTLE_ENDIAN
	/*
	 * On big endian systems changing a 64-bit variable would set the high
	 * 32 bits instead of the low 32 bits, which could cause unexpected
	 * results.
	 */
	fprintf(stderr, "Setting global variables is only supported on "
	    "little-endian systems\n", varname);
	return (ENOTSUP);
#endif
	if ((varval = strchr(arg, '=')) != NULL) {
		*varval = '\0';
		varval++;
		val = strtoull(varval, NULL, 0);
		if (val > UINT32_MAX) {
			fprintf(stderr, "Value for global variable '%s' must "
			    "be a 32-bit unsigned integer\n", varname);
			return (EOVERFLOW);
		}
	} else {
		return (EINVAL);
	}

	zpoolhdl = dlopen("libzpool.so", RTLD_LAZY);
	if (zpoolhdl != NULL) {
		uint32_t *var;
		var = dlsym(zpoolhdl, varname);
		if (var == NULL) {
			fprintf(stderr, "Global variable '%s' does not exist "
			    "in libzpool.so\n", varname);
			return (EINVAL);
		}
		*var = (uint32_t)val;

		dlclose(zpoolhdl);
	} else {
		fprintf(stderr, "Failed to open libzpool.so to set global "
		    "variable\n");
		return (EIO);
	}

	return (0);
}