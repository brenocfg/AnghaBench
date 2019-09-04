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
struct psynch_cvclrprepost_args {int /*<<< orphan*/  flags; int /*<<< orphan*/  preposeq; int /*<<< orphan*/  prepocnt; int /*<<< orphan*/  cvsgen; int /*<<< orphan*/  cvugen; int /*<<< orphan*/  cvgen; int /*<<< orphan*/  cv; } ;
typedef  int /*<<< orphan*/  proc_t ;
struct TYPE_2__ {int (* psynch_cvclrprepost ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ;} ;

/* Variables and functions */
 TYPE_1__* pthread_functions ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

int
psynch_cvclrprepost(proc_t p, struct psynch_cvclrprepost_args * uap, int *retval)
{
	return pthread_functions->psynch_cvclrprepost(p, uap->cv, uap->cvgen, uap->cvugen, uap->cvsgen, uap->prepocnt, uap->preposeq, uap->flags, retval);
}