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
 int /*<<< orphan*/ * PyDict_GetItemString (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * PyImport_AddModule (char*) ; 
 int /*<<< orphan*/ * PyModule_GetDict (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyObject_CallObject (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  handler_call_die (char*) ; 
 int /*<<< orphan*/ * main_dict ; 
 int /*<<< orphan*/ * main_module ; 

__attribute__((used)) static int run_start_sub(void)
{
	PyObject *handler, *retval;
	int err = 0;

	main_module = PyImport_AddModule("__main__");
	if (main_module == NULL)
		return -1;
	Py_INCREF(main_module);

	main_dict = PyModule_GetDict(main_module);
	if (main_dict == NULL) {
		err = -1;
		goto error;
	}
	Py_INCREF(main_dict);

	handler = PyDict_GetItemString(main_dict, "trace_begin");
	if (handler == NULL || !PyCallable_Check(handler))
		goto out;

	retval = PyObject_CallObject(handler, NULL);
	if (retval == NULL)
		handler_call_die("trace_begin");

	Py_DECREF(retval);
	return err;
error:
	Py_XDECREF(main_dict);
	Py_XDECREF(main_module);
out:
	return err;
}