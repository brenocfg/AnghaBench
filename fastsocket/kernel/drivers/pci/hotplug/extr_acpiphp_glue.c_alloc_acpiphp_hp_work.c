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
typedef  int /*<<< orphan*/  u32 ;
struct acpiphp_hp_work {int /*<<< orphan*/  work; void* context; int /*<<< orphan*/  type; int /*<<< orphan*/  handle; } ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,void (*) (struct work_struct*)) ; 
 int /*<<< orphan*/  kacpi_hotplug_wq ; 
 int /*<<< orphan*/  kfree (struct acpiphp_hp_work*) ; 
 struct acpiphp_hp_work* kmalloc (int,int /*<<< orphan*/ ) ; 
 int queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void alloc_acpiphp_hp_work(acpi_handle handle, u32 type,
				  void *context,
				  void (*func)(struct work_struct *work))
{
	struct acpiphp_hp_work *hp_work;
	int ret;

	hp_work = kmalloc(sizeof(*hp_work), GFP_KERNEL);
	if (!hp_work)
		return;

	hp_work->handle = handle;
	hp_work->type = type;
	hp_work->context = context;

	INIT_WORK(&hp_work->work, func);
	ret = queue_work(kacpi_hotplug_wq, &hp_work->work);
	if (!ret)
		kfree(hp_work);
}