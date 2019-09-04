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
struct psynch_cvbroad_args {int /*<<< orphan*/  tid; int /*<<< orphan*/  mugen; int /*<<< orphan*/  mutex; int /*<<< orphan*/  flags; int /*<<< orphan*/  cvudgen; int /*<<< orphan*/  cvlsgen; int /*<<< orphan*/  cv; } ;
typedef  int /*<<< orphan*/  proc_t ;
struct TYPE_2__ {int (* psynch_cvbroad ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 TYPE_1__* pthread_functions ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
psynch_cvbroad(proc_t p, struct psynch_cvbroad_args *uap, uint32_t *retval)
{
	return pthread_functions->psynch_cvbroad(p, uap->cv, uap->cvlsgen, uap->cvudgen, uap->flags, uap->mutex, uap->mugen, uap->tid, retval);
}