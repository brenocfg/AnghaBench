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
struct TYPE_2__ {int size; int /*<<< orphan*/ * container; } ;
struct cpp_demangle_data {long cur; TYPE_1__ output; int /*<<< orphan*/  last_sname; int /*<<< orphan*/  cmd; } ;

/* Variables and functions */
 int DEM_PUSH_STR (struct cpp_demangle_data*,char*) ; 
 int /*<<< orphan*/  READ_TMPL ; 
 int /*<<< orphan*/  assert (int) ; 
 int cpp_demangle_push_str (struct cpp_demangle_data*,long,long) ; 
 scalar_t__ cpp_demangle_read_number (struct cpp_demangle_data*,long*) ; 
 scalar_t__ memcmp (char*,long,int) ; 
 int /*<<< orphan*/ * vector_read_cmd_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cpp_demangle_read_sname(struct cpp_demangle_data *ddata)
{
	long len;
	int err;

	if (ddata == NULL || cpp_demangle_read_number(ddata, &len) == 0 ||
	    len <= 0)
		return (0);

	if (len == 12 && (memcmp("_GLOBAL__N_1", ddata->cur, 12) == 0))
		err = DEM_PUSH_STR(ddata, "(anonymous namespace)");
	else
		err = cpp_demangle_push_str(ddata, ddata->cur, len);

	if (err == 0)
		return (0);

	assert(ddata->output.size > 0);
	if (vector_read_cmd_find(&ddata->cmd, READ_TMPL) == NULL)
		ddata->last_sname =
		    ddata->output.container[ddata->output.size - 1];

	ddata->cur += len;

	return (1);
}