#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vector_type_qualifier {int dummy; } ;
struct TYPE_4__ {size_t size; } ;
struct cpp_demangle_data {char* cur; int func_type; int /*<<< orphan*/  cmd; TYPE_1__ class_type; TYPE_1__ output; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEM_PUSH_STR (struct cpp_demangle_data*,char*) ; 
 int /*<<< orphan*/  READ_PTRMEM ; 
 int /*<<< orphan*/  cpp_demangle_push_str (struct cpp_demangle_data*,char*,size_t) ; 
 int /*<<< orphan*/  cpp_demangle_read_type (struct cpp_demangle_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  vector_read_cmd_pop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vector_read_cmd_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct vector_type_qualifier*) ; 
 int /*<<< orphan*/  vector_str_pop (TYPE_1__*) ; 
 int /*<<< orphan*/  vector_str_push (TYPE_1__*,char*,size_t) ; 
 char* vector_str_substr (TYPE_1__*,size_t,int,size_t*) ; 
 int /*<<< orphan*/  vector_type_qualifier_dest (struct vector_type_qualifier*) ; 
 int /*<<< orphan*/  vector_type_qualifier_init (struct vector_type_qualifier*) ; 

__attribute__((used)) static int
cpp_demangle_read_pointer_to_member(struct cpp_demangle_data *ddata,
    struct vector_type_qualifier *v)
{
	size_t class_type_len, i, idx, p_idx;
	int p_func_type, rtn;
	char *class_type;

	if (ddata == NULL || *ddata->cur != 'M' || *(++ddata->cur) == '\0')
		return (0);

	p_idx = ddata->output.size;
	if (!cpp_demangle_read_type(ddata, NULL))
		return (0);

	if ((class_type = vector_str_substr(&ddata->output, p_idx,
	    ddata->output.size - 1, &class_type_len)) == NULL)
		return (0);

	rtn = 0;
	idx = ddata->output.size;
	for (i = p_idx; i < idx; ++i)
		if (!vector_str_pop(&ddata->output))
			goto clean1;

	if (!vector_read_cmd_push(&ddata->cmd, READ_PTRMEM, v))
		goto clean1;

	if (!vector_str_push(&ddata->class_type, class_type, class_type_len))
		goto clean2;

	p_func_type = ddata->func_type;
	if (!cpp_demangle_read_type(ddata, NULL))
		goto clean3;

	if (p_func_type == ddata->func_type) {
		if (!DEM_PUSH_STR(ddata, " "))
			goto clean3;
		if (!cpp_demangle_push_str(ddata, class_type, class_type_len))
			goto clean3;
		if (!DEM_PUSH_STR(ddata, "::*"))
			goto clean3;
	}

	rtn = 1;
clean3:
	if (!vector_str_pop(&ddata->class_type))
		rtn = 0;
clean2:
	if (!vector_read_cmd_pop(&ddata->cmd))
		rtn = 0;
clean1:
	free(class_type);

	vector_type_qualifier_dest(v);
	if (!vector_type_qualifier_init(v))
		return (0);

	return (rtn);
}