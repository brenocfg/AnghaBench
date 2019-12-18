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
typedef  enum print_arg_type { ____Placeholder_print_arg_type } print_arg_type ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int PRINT_FLAGS ; 
 int PRINT_SYMBOL ; 
 scalar_t__ PyCallable_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyDict_GetItemString (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * PyObject_CallObject (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyString_FromString (char const*) ; 
 int /*<<< orphan*/ * PyTuple_New (int) ; 
 int /*<<< orphan*/  PyTuple_SetItem (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_FatalError (char*) ; 
 int /*<<< orphan*/  handler_call_die (char const*) ; 
 int /*<<< orphan*/  main_dict ; 

__attribute__((used)) static void define_field(enum print_arg_type field_type,
			 const char *ev_name,
			 const char *field_name,
			 const char *delim)
{
	const char *handler_name = "define_flag_field";
	PyObject *handler, *t, *retval;
	unsigned n = 0;

	if (field_type == PRINT_SYMBOL)
		handler_name = "define_symbolic_field";

	if (field_type == PRINT_FLAGS)
		t = PyTuple_New(3);
	else
		t = PyTuple_New(2);
	if (!t)
		Py_FatalError("couldn't create Python tuple");

	PyTuple_SetItem(t, n++, PyString_FromString(ev_name));
	PyTuple_SetItem(t, n++, PyString_FromString(field_name));
	if (field_type == PRINT_FLAGS)
		PyTuple_SetItem(t, n++, PyString_FromString(delim));

	handler = PyDict_GetItemString(main_dict, handler_name);
	if (handler && PyCallable_Check(handler)) {
		retval = PyObject_CallObject(handler, t);
		if (retval == NULL)
			handler_call_die(handler_name);
	}

	Py_DECREF(t);
}