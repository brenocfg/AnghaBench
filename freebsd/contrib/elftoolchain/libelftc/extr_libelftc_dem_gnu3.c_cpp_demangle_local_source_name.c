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
 int /*<<< orphan*/  cpp_demangle_read_sname (struct cpp_demangle_data*) ; 

__attribute__((used)) static int
cpp_demangle_local_source_name(struct cpp_demangle_data *ddata)
{
	/* L */
	if (ddata == NULL || *ddata->cur != 'L')
		return (0);
	++ddata->cur;

	/* source name */
	if (!cpp_demangle_read_sname(ddata))
		return (0);

	/* discriminator */
	if (*ddata->cur == '_') {
		++ddata->cur;
		while (ELFTC_ISDIGIT(*ddata->cur) != 0)
			++ddata->cur;
	}

	return (1);
}