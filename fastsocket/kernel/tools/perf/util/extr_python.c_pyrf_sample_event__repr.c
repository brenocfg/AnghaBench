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
struct pyrf_event {int dummy; } ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/ * PyErr_NoMemory () ; 
 int /*<<< orphan*/ * PyString_FromString (char*) ; 
 scalar_t__ asprintf (char**,char*) ; 
 int /*<<< orphan*/  free (char*) ; 

__attribute__((used)) static PyObject *pyrf_sample_event__repr(struct pyrf_event *pevent)
{
	PyObject *ret;
	char *s;

	if (asprintf(&s, "{ type: sample }") < 0) {
		ret = PyErr_NoMemory();
	} else {
		ret = PyString_FromString(s);
		free(s);
	}
	return ret;
}