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
struct cpp_demangle_data {char* cur; } ;

/* Variables and functions */
 scalar_t__ ELFTC_ISDIGIT (char) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ errno ; 
 long strtol (char*,char**,int) ; 

__attribute__((used)) static int
cpp_demangle_read_number(struct cpp_demangle_data *ddata, long *rtn)
{
	long len, negative_factor;

	if (ddata == NULL || rtn == NULL)
		return (0);

	negative_factor = 1;
	if (*ddata->cur == 'n') {
		negative_factor = -1;

		++ddata->cur;
	}
	if (ELFTC_ISDIGIT(*ddata->cur) == 0)
		return (0);

	errno = 0;
	if ((len = strtol(ddata->cur, (char **) NULL, 10)) == 0 &&
	    errno != 0)
		return (0);

	while (ELFTC_ISDIGIT(*ddata->cur) != 0)
		++ddata->cur;

	assert(len >= 0);
	assert(negative_factor == 1 || negative_factor == -1);

	*rtn = len * negative_factor;

	return (1);
}