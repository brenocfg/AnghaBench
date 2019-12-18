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
 scalar_t__ PyBytes_AsString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyBytes_Check (int /*<<< orphan*/ *) ; 
 int PyBytes_Size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_TypeError ; 

__attribute__((used)) static PyObject *
_optr_to_object(PyObject *bytes)
{
    if(!PyBytes_Check(bytes)) {
        PyErr_SetString(PyExc_TypeError, "Cannot unwrap non-bytes object");
        return NULL;
    }
    if(PyBytes_Size(bytes) != sizeof(void*)) {
        PyErr_SetString(PyExc_TypeError, "Invalid length of bytes object");
        return NULL;
    }
    PyObject *object = * (PyObject **) PyBytes_AsString(bytes);
    return object;
}