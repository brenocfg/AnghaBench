#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  tp_new; } ;

/* Variables and functions */
 int /*<<< orphan*/  PyType_GenericNew ; 
 int PyType_Ready (TYPE_1__*) ; 
 TYPE_1__ pyrf_evlist__type ; 

__attribute__((used)) static int pyrf_evlist__setup_types(void)
{
	pyrf_evlist__type.tp_new = PyType_GenericNew;
	return PyType_Ready(&pyrf_evlist__type);
}