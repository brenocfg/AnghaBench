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
typedef  int /*<<< orphan*/  uint32_t ;
struct psynch_cvsignal_args {int /*<<< orphan*/  flags; int /*<<< orphan*/  tid; int /*<<< orphan*/  mugen; int /*<<< orphan*/  mutex; int /*<<< orphan*/  thread_port; int /*<<< orphan*/  cvugen; int /*<<< orphan*/  cvlsgen; int /*<<< orphan*/  cv; } ;
typedef  int /*<<< orphan*/  proc_t ;
struct TYPE_2__ {int (* psynch_cvsignal ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 TYPE_1__* pthread_functions ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
psynch_cvsignal(proc_t p, struct psynch_cvsignal_args *uap, uint32_t *retval)
{
	return pthread_functions->psynch_cvsignal(p, uap->cv, uap->cvlsgen, uap->cvugen, uap->thread_port, uap->mutex, uap->mugen, uap->tid, uap->flags, retval);
}