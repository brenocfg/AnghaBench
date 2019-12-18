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
typedef  union perf_event {int dummy; } perf_event ;
struct perf_evlist {int dummy; } ;
struct pyrf_evlist {struct perf_evlist evlist; } ;
struct pyrf_event {int /*<<< orphan*/  sample; } ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/  PyArg_ParseTupleAndKeywords (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char**,int*,int*) ; 
 int /*<<< orphan*/ * PyErr_Format (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/ * PyErr_NoMemory () ; 
 int /*<<< orphan*/  PyExc_OSError ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Py_None ; 
 union perf_event* perf_evlist__mmap_read (struct perf_evlist*,int) ; 
 int perf_evlist__parse_sample (struct perf_evlist*,union perf_event*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pyrf_event__new (union perf_event*) ; 

__attribute__((used)) static PyObject *pyrf_evlist__read_on_cpu(struct pyrf_evlist *pevlist,
					  PyObject *args, PyObject *kwargs)
{
	struct perf_evlist *evlist = &pevlist->evlist;
	union perf_event *event;
	int sample_id_all = 1, cpu;
	static char *kwlist[] = { "cpu", "sample_id_all", NULL };
	int err;

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i|i", kwlist,
					 &cpu, &sample_id_all))
		return NULL;

	event = perf_evlist__mmap_read(evlist, cpu);
	if (event != NULL) {
		PyObject *pyevent = pyrf_event__new(event);
		struct pyrf_event *pevent = (struct pyrf_event *)pyevent;

		if (pyevent == NULL)
			return PyErr_NoMemory();

		err = perf_evlist__parse_sample(evlist, event, &pevent->sample);
		if (err)
			return PyErr_Format(PyExc_OSError,
					    "perf: can't parse sample, err=%d", err);
		return pyevent;
	}

	Py_INCREF(Py_None);
	return Py_None;
}