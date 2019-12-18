#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pyrf_cpu_map {TYPE_1__* cpus; } ;
struct TYPE_2__ {int /*<<< orphan*/  nr; } ;
typedef  int /*<<< orphan*/  Py_ssize_t ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */

__attribute__((used)) static Py_ssize_t pyrf_cpu_map__length(PyObject *obj)
{
	struct pyrf_cpu_map *pcpus = (void *)obj;

	return pcpus->cpus->nr;
}