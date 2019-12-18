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
struct perf_evlist {int /*<<< orphan*/  nr_fds; int /*<<< orphan*/  pollfd; } ;
struct pyrf_evlist {struct perf_evlist evlist; } ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/  PyArg_ParseTupleAndKeywords (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char**,int*) ; 
 int /*<<< orphan*/  PyErr_SetFromErrno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyExc_OSError ; 
 int /*<<< orphan*/ * Py_BuildValue (char*,int) ; 
 int poll (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static PyObject *pyrf_evlist__poll(struct pyrf_evlist *pevlist,
				   PyObject *args, PyObject *kwargs)
{
	struct perf_evlist *evlist = &pevlist->evlist;
	static char *kwlist[] = { "timeout", NULL };
	int timeout = -1, n;

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "|i", kwlist, &timeout))
		return NULL;

	n = poll(evlist->pollfd, evlist->nr_fds, timeout);
	if (n < 0) {
		PyErr_SetFromErrno(PyExc_OSError);
		return NULL;
	}

	return Py_BuildValue("i", n);
}