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
struct vector_str {size_t size; } ;
struct cpp_demangle_data {char* cur; int mem_rst; int mem_vat; int mem_cst; int mem_ref; int mem_rref; struct vector_str* cur_output; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_DEMANGLE_TRY_LIMIT ; 
 int /*<<< orphan*/  DEM_PUSH_STR (struct cpp_demangle_data*,char*) ; 
 int /*<<< orphan*/  VEC_PUSH_STR (struct vector_str*,char*) ; 
 int /*<<< orphan*/  cpp_demangle_push_subst_v (struct cpp_demangle_data*,struct vector_str*) ; 
 int /*<<< orphan*/  cpp_demangle_read_subst (struct cpp_demangle_data*) ; 
 int /*<<< orphan*/  cpp_demangle_read_tmpl_args (struct cpp_demangle_data*) ; 
 int /*<<< orphan*/  cpp_demangle_read_tmpl_param (struct cpp_demangle_data*) ; 
 int /*<<< orphan*/  cpp_demangle_read_uqname (struct cpp_demangle_data*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  vector_str_dest (struct vector_str*) ; 
 int /*<<< orphan*/  vector_str_init (struct vector_str*) ; 
 int /*<<< orphan*/  vector_str_push (struct vector_str*,char*,size_t) ; 
 char* vector_str_substr (struct vector_str*,size_t,int,size_t*) ; 

__attribute__((used)) static int
cpp_demangle_read_nested_name(struct cpp_demangle_data *ddata)
{
	struct vector_str *output, v;
	size_t limit, p_idx, subst_str_len;
	int rtn;
	char *subst_str;

	if (ddata == NULL || *ddata->cur != 'N')
		return (0);
	if (*(++ddata->cur) == '\0')
		return (0);

	do {
		switch (*ddata->cur) {
		case 'r':
			ddata->mem_rst = true;
			break;
		case 'V':
			ddata->mem_vat = true;
			break;
		case 'K':
			ddata->mem_cst = true;
			break;
		case 'R':
			ddata->mem_ref = true;
			break;
		case 'O':
			ddata->mem_rref = true;
			break;
		default:
			goto next;
		}
	} while (*(++ddata->cur));

next:
	output = ddata->cur_output;
	if (!vector_str_init(&v))
		return (0);

	rtn = 0;
	limit = 0;
	for (;;) {
		p_idx = output->size;
		switch (*ddata->cur) {
		case 'I':
			if (!cpp_demangle_read_tmpl_args(ddata))
				goto clean;
			break;
		case 'S':
			if (!cpp_demangle_read_subst(ddata))
				goto clean;
			break;
		case 'T':
			if (!cpp_demangle_read_tmpl_param(ddata))
				goto clean;
			break;
		default:
			if (!cpp_demangle_read_uqname(ddata))
				goto clean;
		}

		if (p_idx == output->size)
			goto next_comp;
		if ((subst_str = vector_str_substr(output, p_idx,
		    output->size - 1, &subst_str_len)) == NULL)
			goto clean;
		if (!vector_str_push(&v, subst_str, subst_str_len)) {
			free(subst_str);
			goto clean;
		}
		free(subst_str);

		if (!cpp_demangle_push_subst_v(ddata, &v))
			goto clean;

	next_comp:
		if (*ddata->cur == 'E')
			break;
		else if (*ddata->cur != 'I' && *ddata->cur != 'C' &&
		    *ddata->cur != 'D' && p_idx != output->size) {
			if (!DEM_PUSH_STR(ddata, "::"))
				goto clean;
			if (!VEC_PUSH_STR(&v, "::"))
				goto clean;
		}
		if (limit++ > CPP_DEMANGLE_TRY_LIMIT)
			goto clean;
	}

	++ddata->cur;
	rtn = 1;

clean:
	vector_str_dest(&v);

	return (rtn);
}