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
struct TYPE_2__ {int /*<<< orphan*/  id; int /*<<< orphan*/ * cls; } ;
struct mpic {struct mpic* next; TYPE_1__ sysdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  mpic_sysclass ; 
 struct mpic* mpics ; 
 int sysdev_class_register (int /*<<< orphan*/ *) ; 
 int sysdev_register (TYPE_1__*) ; 

__attribute__((used)) static int mpic_init_sys(void)
{
	struct mpic *mpic = mpics;
	int error, id = 0;

	error = sysdev_class_register(&mpic_sysclass);

	while (mpic && !error) {
		mpic->sysdev.cls = &mpic_sysclass;
		mpic->sysdev.id = id++;
		error = sysdev_register(&mpic->sysdev);
		mpic = mpic->next;
	}
	return error;
}