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
typedef  char* uint64_t ;
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  char* boolean_t ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
#define  DATA_TYPE_BOOLEAN 132 
#define  DATA_TYPE_BOOLEAN_VALUE 131 
#define  DATA_TYPE_NVLIST 130 
#define  DATA_TYPE_STRING 129 
#define  DATA_TYPE_UINT64 128 
 int /*<<< orphan*/ * PyDict_New () ; 
 int /*<<< orphan*/  PyDict_SetItemString (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyErr_SetNone (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 int /*<<< orphan*/ * Py_BuildValue (char*,char*) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Py_None ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvpair_name (int /*<<< orphan*/ *) ; 
 int nvpair_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvpair_value_boolean_value (int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  nvpair_value_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  nvpair_value_string (int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  nvpair_value_uint64 (int /*<<< orphan*/ *,char**) ; 

__attribute__((used)) static PyObject *
nvl2py(nvlist_t *nvl)
{
	PyObject *pyo;
	nvpair_t *nvp;

	pyo = PyDict_New();

	for (nvp = nvlist_next_nvpair(nvl, NULL); nvp;
	    nvp = nvlist_next_nvpair(nvl, nvp)) {
		PyObject *pyval;
		char *sval;
		uint64_t ival;
		boolean_t bval;
		nvlist_t *nval;

		switch (nvpair_type(nvp)) {
		case DATA_TYPE_STRING:
			(void) nvpair_value_string(nvp, &sval);
			pyval = Py_BuildValue("s", sval);
			break;

		case DATA_TYPE_UINT64:
			(void) nvpair_value_uint64(nvp, &ival);
			pyval = Py_BuildValue("K", ival);
			break;

		case DATA_TYPE_NVLIST:
			(void) nvpair_value_nvlist(nvp, &nval);
			pyval = nvl2py(nval);
			break;

		case DATA_TYPE_BOOLEAN:
			Py_INCREF(Py_None);
			pyval = Py_None;
			break;

		case DATA_TYPE_BOOLEAN_VALUE:
			(void) nvpair_value_boolean_value(nvp, &bval);
			pyval = Py_BuildValue("i", bval);
			break;

		default:
			PyErr_SetNone(PyExc_ValueError);
			Py_DECREF(pyo);
			return (NULL);
		}

		PyDict_SetItemString(pyo, nvpair_name(nvp), pyval);
		Py_DECREF(pyval);
	}

	return (pyo);
}