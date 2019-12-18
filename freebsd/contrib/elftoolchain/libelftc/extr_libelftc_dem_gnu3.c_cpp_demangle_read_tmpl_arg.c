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
 int cpp_demangle_read_expr_primary (struct cpp_demangle_data*) ; 
 int /*<<< orphan*/  cpp_demangle_read_expression (struct cpp_demangle_data*) ; 
 int cpp_demangle_read_type (struct cpp_demangle_data*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
cpp_demangle_read_tmpl_arg(struct cpp_demangle_data *ddata)
{

	if (ddata == NULL || *ddata->cur == '\0')
		return (0);

	switch (*ddata->cur) {
	case 'L':
		return (cpp_demangle_read_expr_primary(ddata));
	case 'X':
		++ddata->cur;
		if (!cpp_demangle_read_expression(ddata))
			return (0);
		return (*ddata->cur++ == 'E');
	}

	return (cpp_demangle_read_type(ddata, NULL));
}