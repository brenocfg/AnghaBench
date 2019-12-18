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
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/  PyCallable_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyDict_GetItemString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * PyObject_CallObject (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_Finalize () ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handler_call_die (char*) ; 
 int /*<<< orphan*/  main_dict ; 
 int /*<<< orphan*/  main_module ; 

__attribute__((used)) static int python_stop_script(void)
{
	PyObject *handler, *retval;
	int err = 0;

	handler = PyDict_GetItemString(main_dict, "trace_end");
	if (handler == NULL || !PyCallable_Check(handler))
		goto out;

	retval = PyObject_CallObject(handler, NULL);
	if (retval == NULL)
		handler_call_die("trace_end");
	else
		Py_DECREF(retval);
out:
	Py_XDECREF(main_dict);
	Py_XDECREF(main_module);
	Py_Finalize();

	return err;
}