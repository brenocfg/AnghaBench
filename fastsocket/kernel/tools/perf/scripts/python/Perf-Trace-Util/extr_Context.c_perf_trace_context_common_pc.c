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
struct scripting_context {int dummy; } ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/  PyArg_ParseTuple (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **) ; 
 struct scripting_context* PyCObject_AsVoidPtr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Py_BuildValue (char*,int) ; 
 int common_pc (struct scripting_context*) ; 

__attribute__((used)) static PyObject *perf_trace_context_common_pc(PyObject *self, PyObject *args)
{
	static struct scripting_context *scripting_context;
	PyObject *context;
	int retval;

	if (!PyArg_ParseTuple(args, "O", &context))
		return NULL;

	scripting_context = PyCObject_AsVoidPtr(context);
	retval = common_pc(scripting_context);

	return Py_BuildValue("i", retval);
}