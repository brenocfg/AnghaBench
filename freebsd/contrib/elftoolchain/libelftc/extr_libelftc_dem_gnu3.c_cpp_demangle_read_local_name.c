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
struct vector_str {int dummy; } ;
struct type_delimit {int paren; int firstp; } ;
struct cpp_demangle_data {char* cur; int is_tmpl; struct vector_str output; struct vector_str* cur_output; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_DEMANGLE_TRY_LIMIT ; 
 int /*<<< orphan*/  DEM_PUSH_STR (struct cpp_demangle_data*,char*) ; 
 scalar_t__ ELFTC_ISDIGIT (char) ; 
 int /*<<< orphan*/  cpp_demangle_read_encoding (struct cpp_demangle_data*) ; 
 int /*<<< orphan*/  cpp_demangle_read_name (struct cpp_demangle_data*) ; 
 int /*<<< orphan*/  cpp_demangle_read_type (struct cpp_demangle_data*,struct type_delimit*) ; 
 int /*<<< orphan*/  vector_str_dest (struct vector_str*) ; 
 int /*<<< orphan*/  vector_str_init (struct vector_str*) ; 
 int /*<<< orphan*/  vector_str_push_vector (struct vector_str*,struct vector_str*) ; 

__attribute__((used)) static int
cpp_demangle_read_local_name(struct cpp_demangle_data *ddata)
{
	struct vector_str local_name;
	struct type_delimit td;
	size_t limit;
	bool  more_type;

	if (ddata == NULL)
		return (0);
	if (*(++ddata->cur) == '\0')
		return (0);

	vector_str_init(&local_name);
	ddata->cur_output = &local_name;

	if (!cpp_demangle_read_encoding(ddata)) {
		vector_str_dest(&local_name);
		return (0);
	}

	ddata->cur_output = &ddata->output;

	td.paren = false;
	td.firstp = true;
	more_type = false;
	limit = 0;

	/*
	 * The first type is a return type if we just demangled template
	 * args. (the template args is right next to the function name,
	 * which means it's a template function)
	 */
	if (ddata->is_tmpl) {
		ddata->is_tmpl = false;

		/* Read return type */
		if (!cpp_demangle_read_type(ddata, NULL)) {
			vector_str_dest(&local_name);
			return (0);
		}

		more_type = true;
	}

	/* Now we can push the name after possible return type is handled. */
	if (!vector_str_push_vector(&ddata->output, &local_name)) {
		vector_str_dest(&local_name);
		return (0);
	}
	vector_str_dest(&local_name);

	while (*ddata->cur != '\0') {
		if (!cpp_demangle_read_type(ddata, &td))
			return (0);
		if (more_type)
			more_type = false;
		if (*ddata->cur == 'E')
			break;
		if (limit++ > CPP_DEMANGLE_TRY_LIMIT)
			return (0);
	}
	if (more_type)
		return (0);

	if (*(++ddata->cur) == '\0')
		return (0);
	if (td.paren == true) {
		if (!DEM_PUSH_STR(ddata, ")"))
			return (0);
		td.paren = false;
	}
	if (*ddata->cur == 's')
		++ddata->cur;
	else {
		if (!DEM_PUSH_STR(ddata, "::"))
			return (0);
		if (!cpp_demangle_read_name(ddata))
			return (0);
	}
	if (*ddata->cur == '_') {
		++ddata->cur;
		while (ELFTC_ISDIGIT(*ddata->cur) != 0)
			++ddata->cur;
	}

	return (1);
}