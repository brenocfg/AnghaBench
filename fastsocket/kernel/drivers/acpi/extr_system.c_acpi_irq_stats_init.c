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
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct kobj_attribute {int dummy; } ;
struct event_counter {int dummy; } ;
struct attribute {int dummy; } ;
struct TYPE_7__ {char* name; int mode; } ;
struct TYPE_6__ {TYPE_4__ attr; int /*<<< orphan*/  store; int /*<<< orphan*/  show; } ;
struct TYPE_5__ {TYPE_4__** attrs; } ;

/* Variables and functions */
 int ACPI_EVENT_GLOBAL ; 
 int ACPI_EVENT_PMTIMER ; 
 int ACPI_EVENT_POWER_BUTTON ; 
 int ACPI_EVENT_RTC ; 
 int ACPI_EVENT_SLEEP_BUTTON ; 
 int ACPI_NUM_FIXED_EVENTS ; 
 int COUNT_ERROR ; 
 int COUNT_GPE ; 
 int COUNT_SCI ; 
 int COUNT_SCI_NOT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int NUM_COUNTERS_EXTRA ; 
 int acpi_current_gpe_count ; 
 int /*<<< orphan*/  acpi_kobj ; 
 TYPE_4__** all_attrs ; 
 int /*<<< orphan*/ * all_counters ; 
 TYPE_3__* counter_attrs ; 
 int /*<<< orphan*/  counter_set ; 
 int /*<<< orphan*/  counter_show ; 
 int /*<<< orphan*/  delete_gpe_attr_array () ; 
 TYPE_1__ interrupt_stats_attr_group ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int num_counters ; 
 int num_gpes ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 int /*<<< orphan*/  sysfs_create_group (int /*<<< orphan*/ ,TYPE_1__*) ; 

void acpi_irq_stats_init(void)
{
	int i;

	if (all_counters)
		return;

	num_gpes = acpi_current_gpe_count;
	num_counters = num_gpes + ACPI_NUM_FIXED_EVENTS + NUM_COUNTERS_EXTRA;

	all_attrs = kzalloc(sizeof(struct attribute *) * (num_counters + 1),
			GFP_KERNEL);
	if (all_attrs == NULL)
		return;

	all_counters = kzalloc(sizeof(struct event_counter) * (num_counters),
				GFP_KERNEL);
	if (all_counters == NULL)
		goto fail;

	counter_attrs = kzalloc(sizeof(struct kobj_attribute) * (num_counters),
			GFP_KERNEL);
	if (counter_attrs == NULL)
		goto fail;

	for (i = 0; i < num_counters; ++i) {
		char buffer[12];
		char *name;

		if (i < num_gpes)
			sprintf(buffer, "gpe%02X", i);
		else if (i == num_gpes + ACPI_EVENT_PMTIMER)
			sprintf(buffer, "ff_pmtimer");
		else if (i == num_gpes + ACPI_EVENT_GLOBAL)
			sprintf(buffer, "ff_gbl_lock");
		else if (i == num_gpes + ACPI_EVENT_POWER_BUTTON)
			sprintf(buffer, "ff_pwr_btn");
		else if (i == num_gpes + ACPI_EVENT_SLEEP_BUTTON)
			sprintf(buffer, "ff_slp_btn");
		else if (i == num_gpes + ACPI_EVENT_RTC)
			sprintf(buffer, "ff_rt_clk");
		else if (i == num_gpes + ACPI_NUM_FIXED_EVENTS + COUNT_GPE)
			sprintf(buffer, "gpe_all");
		else if (i == num_gpes + ACPI_NUM_FIXED_EVENTS + COUNT_SCI)
			sprintf(buffer, "sci");
		else if (i == num_gpes + ACPI_NUM_FIXED_EVENTS + COUNT_SCI_NOT)
			sprintf(buffer, "sci_not");
		else if (i == num_gpes + ACPI_NUM_FIXED_EVENTS + COUNT_ERROR)
			sprintf(buffer, "error");
		else
			sprintf(buffer, "bug%02X", i);

		name = kzalloc(strlen(buffer) + 1, GFP_KERNEL);
		if (name == NULL)
			goto fail;
		strncpy(name, buffer, strlen(buffer) + 1);

		counter_attrs[i].attr.name = name;
		counter_attrs[i].attr.mode = 0644;
		counter_attrs[i].show = counter_show;
		counter_attrs[i].store = counter_set;

		all_attrs[i] = &counter_attrs[i].attr;
	}

	interrupt_stats_attr_group.attrs = all_attrs;
	if (!sysfs_create_group(acpi_kobj, &interrupt_stats_attr_group))
		return;

fail:
	delete_gpe_attr_array();
	return;
}