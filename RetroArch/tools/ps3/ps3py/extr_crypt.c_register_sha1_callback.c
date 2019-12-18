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
 scalar_t__ PyArg_ParseTuple (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  PyCallable_Check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_TypeError ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Py_None ; 
 int /*<<< orphan*/  Py_XDECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_XINCREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sha1_callback ; 

__attribute__((used)) static PyObject *register_sha1_callback(PyObject *self, PyObject *args)
{
   PyObject *result = NULL;
   PyObject *temp;

   if (PyArg_ParseTuple(args, "O:set_callback", &temp))
   {
      if (!PyCallable_Check(temp))
      {
         PyErr_SetString(PyExc_TypeError, "parameter must be callable");
         return NULL;
      }
      Py_XINCREF(temp);           /* Add a reference to new callback */
      Py_XDECREF(sha1_callback);  /* Dispose of previous callback */
      sha1_callback = temp;       /* Remember new callback */
                                  /* Boilerplate to return "None" */
      Py_INCREF(Py_None);
      result = Py_None;
   }
   return result;
}