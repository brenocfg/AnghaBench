#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* lcpus; } ;
typedef  TYPE_1__ x86_pkg_t ;
struct TYPE_6__ {TYPE_1__* package; struct TYPE_6__* next_in_pkg; } ;
typedef  TYPE_2__ x86_lcpu_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
x86_package_add_lcpu(x86_pkg_t *pkg, x86_lcpu_t *lcpu)
{
    assert(pkg != NULL);
    assert(lcpu != NULL);

    lcpu->next_in_pkg = pkg->lcpus;
    lcpu->package = pkg;
    pkg->lcpus = lcpu;
}