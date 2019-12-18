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
struct pyrf_thread_map {TYPE_1__* ob_type; int /*<<< orphan*/  threads; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* tp_free ) (int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_map__delete (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pyrf_thread_map__delete(struct pyrf_thread_map *pthreads)
{
	thread_map__delete(pthreads->threads);
	pthreads->ob_type->tp_free((PyObject*)pthreads);
}