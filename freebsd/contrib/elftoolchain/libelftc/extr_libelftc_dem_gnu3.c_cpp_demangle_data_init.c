#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * container; } ;
struct cpp_demangle_data {int mem_rst; int mem_vat; int mem_cst; int mem_ref; int mem_rref; int is_tmpl; int is_functype; int ref_qualifier; char const* cur; TYPE_1__ output; TYPE_1__ subst; TYPE_1__ tmpl; TYPE_1__ class_type; int /*<<< orphan*/ * last_sname; TYPE_1__* cur_output; scalar_t__ func_type; int /*<<< orphan*/  push_qualifier; int /*<<< orphan*/  cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  PUSH_ALL_QUALIFIER ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vector_read_cmd_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vector_str_dest (TYPE_1__*) ; 
 int /*<<< orphan*/  vector_str_init (TYPE_1__*) ; 

__attribute__((used)) static int
cpp_demangle_data_init(struct cpp_demangle_data *d, const char *cur)
{

	if (d == NULL || cur == NULL)
		return (0);

	if (!vector_str_init(&d->output))
		return (0);
	if (!vector_str_init(&d->subst))
		goto clean1;
	if (!vector_str_init(&d->tmpl))
		goto clean2;
	if (!vector_str_init(&d->class_type))
		goto clean3;
	if (!vector_read_cmd_init(&d->cmd))
		goto clean4;

	assert(d->output.container != NULL);
	assert(d->subst.container != NULL);
	assert(d->tmpl.container != NULL);
	assert(d->class_type.container != NULL);

	d->mem_rst = false;
	d->mem_vat = false;
	d->mem_cst = false;
	d->mem_ref = false;
	d->mem_rref = false;
	d->is_tmpl = false;
	d->is_functype = false;
	d->ref_qualifier = false;
	d->push_qualifier = PUSH_ALL_QUALIFIER;
	d->func_type = 0;
	d->cur = cur;
	d->cur_output = &d->output;
	d->last_sname = NULL;

	return (1);

clean4:
	vector_str_dest(&d->class_type);
clean3:
	vector_str_dest(&d->tmpl);
clean2:
	vector_str_dest(&d->subst);
clean1:
	vector_str_dest(&d->output);

	return (0);
}