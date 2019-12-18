#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  machine_flags; } ;
struct TYPE_6__ {TYPE_1__* vm; int /*<<< orphan*/  count; } ;
struct TYPE_5__ {int /*<<< orphan*/  cpi; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOSYS ; 
 int /*<<< orphan*/  MACHINE_FLAG_KVM ; 
 int /*<<< orphan*/  MACHINE_FLAG_VM ; 
 TYPE_4__ S390_lowcore ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stsi (TYPE_2__*,int,int,int) ; 
 TYPE_2__ vmms ; 

void detect_machine_type(void)
{
	/* No VM information? Looks like LPAR */
	if (stsi(&vmms, 3, 2, 2) == -ENOSYS)
		return;
	if (!vmms.count)
		return;

	/* Running under KVM? If not we assume z/VM */
	if (!memcmp(vmms.vm[0].cpi, "\xd2\xe5\xd4", 3))
		S390_lowcore.machine_flags |= MACHINE_FLAG_KVM;
	else
		S390_lowcore.machine_flags |= MACHINE_FLAG_VM;
}