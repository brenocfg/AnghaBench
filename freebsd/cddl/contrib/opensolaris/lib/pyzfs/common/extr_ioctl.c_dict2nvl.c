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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  boolean_t ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  NV_UNIQUE_NAME ; 
 scalar_t__ PyBool_Check (int /*<<< orphan*/ *) ; 
 scalar_t__ PyDict_Check (int /*<<< orphan*/ *) ; 
 scalar_t__ PyDict_Next (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  PyErr_SetObject (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyExc_KeyError ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 int /*<<< orphan*/  PyInt_AsUnsignedLongLongMask (int /*<<< orphan*/ *) ; 
 scalar_t__ PyInt_Check (int /*<<< orphan*/ *) ; 
 char* PyString_AsString (int /*<<< orphan*/ *) ; 
 scalar_t__ PyString_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Py_None ; 
 int /*<<< orphan*/ * Py_True ; 
 int /*<<< orphan*/  assert (int) ; 
 int nvlist_add_boolean (int /*<<< orphan*/ *,char*) ; 
 int nvlist_add_boolean_value (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int nvlist_add_nvlist (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int nvlist_add_string (int /*<<< orphan*/ *,char*,char*) ; 
 int nvlist_add_uint64 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int nvlist_alloc (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static nvlist_t *
dict2nvl(PyObject *d)
{
	nvlist_t *nvl;
	int err;
	PyObject *key, *value;
	int pos = 0;

	if (!PyDict_Check(d)) {
		PyErr_SetObject(PyExc_ValueError, d);
		return (NULL);
	}

	err = nvlist_alloc(&nvl, NV_UNIQUE_NAME, 0);
	assert(err == 0);

	while (PyDict_Next(d, &pos, &key, &value)) {
		char *keystr = PyString_AsString(key);
		if (keystr == NULL) {
			PyErr_SetObject(PyExc_KeyError, key);
			nvlist_free(nvl);
			return (NULL);
		}

		if (PyDict_Check(value)) {
			nvlist_t *valnvl = dict2nvl(value);
			err = nvlist_add_nvlist(nvl, keystr, valnvl);
			nvlist_free(valnvl);
		} else if (value == Py_None) {
			err = nvlist_add_boolean(nvl, keystr);
		} else if (PyString_Check(value)) {
			char *valstr = PyString_AsString(value);
			err = nvlist_add_string(nvl, keystr, valstr);
		} else if (PyInt_Check(value)) {
			uint64_t valint = PyInt_AsUnsignedLongLongMask(value);
			err = nvlist_add_uint64(nvl, keystr, valint);
		} else if (PyBool_Check(value)) {
			boolean_t valbool = value == Py_True ? B_TRUE : B_FALSE;
			err = nvlist_add_boolean_value(nvl, keystr, valbool);
		} else {
			PyErr_SetObject(PyExc_ValueError, value);
			nvlist_free(nvl);
			return (NULL);
		}
		assert(err == 0);
	}

	return (nvl);
}