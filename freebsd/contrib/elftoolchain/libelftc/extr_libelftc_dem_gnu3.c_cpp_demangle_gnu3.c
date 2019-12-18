#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vector_str {scalar_t__ size; } ;
struct type_delimit {int paren; int firstp; } ;
struct TYPE_2__ {int size; } ;
struct cpp_demangle_data {char* cur; int is_tmpl; struct vector_str output; scalar_t__ mem_rref; scalar_t__ mem_ref; scalar_t__ mem_rst; scalar_t__ mem_cst; scalar_t__ mem_vat; struct vector_str* cur_output; TYPE_1__ subst; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_DEMANGLE_TRY_LIMIT ; 
 int /*<<< orphan*/  VEC_PUSH_STR (struct vector_str*,char*) ; 
 int /*<<< orphan*/  cpp_demangle_data_dest (struct cpp_demangle_data*) ; 
 int /*<<< orphan*/  cpp_demangle_data_init (struct cpp_demangle_data*,char const*) ; 
 int /*<<< orphan*/  cpp_demangle_read_encoding (struct cpp_demangle_data*) ; 
 int /*<<< orphan*/  cpp_demangle_read_type (struct cpp_demangle_data*,struct type_delimit*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 
 int /*<<< orphan*/  vector_str_dest (struct vector_str*) ; 
 char* vector_str_get_flat (struct vector_str*,size_t*) ; 
 int /*<<< orphan*/  vector_str_init (struct vector_str*) ; 
 int /*<<< orphan*/  vector_str_pop (TYPE_1__*) ; 
 int /*<<< orphan*/  vector_str_push_vector_head (struct vector_str*,struct vector_str*) ; 

char *
cpp_demangle_gnu3(const char *org)
{
	struct cpp_demangle_data ddata;
	struct vector_str ret_type;
	struct type_delimit td;
	ssize_t org_len;
	unsigned int limit;
	char *rtn;
	bool has_ret, more_type;

	if (org == NULL || (org_len = strlen(org)) < 2)
		return (NULL);

	if (org_len > 11 && !strncmp(org, "_GLOBAL__I_", 11)) {
		if ((rtn = malloc(org_len + 19)) == NULL)
			return (NULL);
		snprintf(rtn, org_len + 19,
		    "global constructors keyed to %s", org + 11);
		return (rtn);
	}

	if (org[0] != '_' || org[1] != 'Z')
		return (NULL);

	if (!cpp_demangle_data_init(&ddata, org + 2))
		return (NULL);

	rtn = NULL;
	has_ret = more_type = false;

	if (!cpp_demangle_read_encoding(&ddata))
		goto clean;

	/*
	 * Pop function name from substitution candidate list.
	 */
	if (*ddata.cur != 0 && ddata.subst.size >= 1) {
		if (!vector_str_pop(&ddata.subst))
			goto clean;
	}

	td.paren = false;
	td.firstp = true;
	limit = 0;

	/*
	 * The first type is a return type if we just demangled template
	 * args. (the template args is right next to the function name,
	 * which means it's a template function)
	 */
	if (ddata.is_tmpl) {
		ddata.is_tmpl = false;
		if (!vector_str_init(&ret_type))
			goto clean;
		ddata.cur_output = &ret_type;
		has_ret = true;
	}

	while (*ddata.cur != '\0') {
		/*
		 * Breaking at some gcc info at tail. e.g) @@GLIBCXX_3.4
		 */
		if (*ddata.cur == '@' && *(ddata.cur + 1) == '@')
			break;

		if (has_ret) {
			/* Read return type */
			if (!cpp_demangle_read_type(&ddata, NULL))
				goto clean;
		} else {
			/* Read function arg type */
			if (!cpp_demangle_read_type(&ddata, &td))
				goto clean;
		}

		if (has_ret) {
			/* Push return type to the beginning */
			if (!VEC_PUSH_STR(&ret_type, " "))
				goto clean;
			if (!vector_str_push_vector_head(&ddata.output,
			    &ret_type))
				goto clean;
			ddata.cur_output = &ddata.output;
			vector_str_dest(&ret_type);
			has_ret = false;
			more_type = true;
		} else if (more_type)
			more_type = false;
		if (limit++ > CPP_DEMANGLE_TRY_LIMIT)
			goto clean;
	}
	if (more_type)
		goto clean;

	if (ddata.output.size == 0)
		goto clean;
	if (td.paren && !VEC_PUSH_STR(&ddata.output, ")"))
		goto clean;
	if (ddata.mem_vat && !VEC_PUSH_STR(&ddata.output, " volatile"))
		goto clean;
	if (ddata.mem_cst && !VEC_PUSH_STR(&ddata.output, " const"))
		goto clean;
	if (ddata.mem_rst && !VEC_PUSH_STR(&ddata.output, " restrict"))
		goto clean;
	if (ddata.mem_ref && !VEC_PUSH_STR(&ddata.output, " &"))
		goto clean;
	if (ddata.mem_rref && !VEC_PUSH_STR(&ddata.output, " &&"))
		goto clean;

	rtn = vector_str_get_flat(&ddata.output, (size_t *) NULL);

clean:
	if (has_ret)
		vector_str_dest(&ret_type);

	cpp_demangle_data_dest(&ddata);

	return (rtn);
}