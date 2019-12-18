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
struct perf_evlist {int dummy; } ;
struct pyrf_evlist {struct perf_evlist evlist; } ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/  PyArg_ParseTupleAndKeywords (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char**,int*,int*) ; 
 int /*<<< orphan*/  PyErr_SetFromErrno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyExc_OSError ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Py_None ; 
 scalar_t__ perf_evlist__mmap (struct perf_evlist*,int,int) ; 

__attribute__((used)) static PyObject *pyrf_evlist__mmap(struct pyrf_evlist *pevlist,
				   PyObject *args, PyObject *kwargs)
{
	struct perf_evlist *evlist = &pevlist->evlist;
	static char *kwlist[] = { "pages", "overwrite", NULL };
	int pages = 128, overwrite = false;

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "|ii", kwlist,
					 &pages, &overwrite))
		return NULL;

	if (perf_evlist__mmap(evlist, pages, overwrite) < 0) {
		PyErr_SetFromErrno(PyExc_OSError);
		return NULL;
	}

	Py_INCREF(Py_None);
	return Py_None;
}