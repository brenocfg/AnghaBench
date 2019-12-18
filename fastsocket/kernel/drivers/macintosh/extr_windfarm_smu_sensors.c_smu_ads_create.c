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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {char* name; int /*<<< orphan*/ * ops; } ;
struct smu_ad_sensor {TYPE_1__ sens; int /*<<< orphan*/  reg; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SMU_SDB_CPUDIODE_ID ; 
 int /*<<< orphan*/  SMU_SDB_CPUVCP_ID ; 
 int /*<<< orphan*/  SMU_SDB_SLOTSPOW_ID ; 
 int /*<<< orphan*/ * cpudiode ; 
 int /*<<< orphan*/ * cpuvcp ; 
 int /*<<< orphan*/  kfree (struct smu_ad_sensor*) ; 
 struct smu_ad_sensor* kmalloc (int,int /*<<< orphan*/ ) ; 
 void* of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * slotspow ; 
 int /*<<< orphan*/  smu_cpuamp_ops ; 
 int /*<<< orphan*/  smu_cputemp_ops ; 
 int /*<<< orphan*/  smu_cpuvolt_ops ; 
 int /*<<< orphan*/  smu_slotspow_ops ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 scalar_t__ wf_register_sensor (TYPE_1__*) ; 

__attribute__((used)) static struct smu_ad_sensor *smu_ads_create(struct device_node *node)
{
	struct smu_ad_sensor *ads;
	const char *c, *l;
	const u32 *v;

	ads = kmalloc(sizeof(struct smu_ad_sensor), GFP_KERNEL);
	if (ads == NULL)
		return NULL;
	c = of_get_property(node, "device_type", NULL);
	l = of_get_property(node, "location", NULL);
	if (c == NULL || l == NULL)
		goto fail;

	/* We currently pick the sensors based on the OF name and location
	 * properties, while Darwin uses the sensor-id's.
	 * The problem with the IDs is that they are model specific while it
	 * looks like apple has been doing a reasonably good job at keeping
	 * the names and locations consistents so I'll stick with the names
	 * and locations for now.
	 */
	if (!strcmp(c, "temp-sensor") &&
	    !strcmp(l, "CPU T-Diode")) {
		ads->sens.ops = &smu_cputemp_ops;
		ads->sens.name = "cpu-temp";
		if (cpudiode == NULL) {
			DBG("wf: cpudiode partition (%02x) not found\n",
			    SMU_SDB_CPUDIODE_ID);
			goto fail;
		}
	} else if (!strcmp(c, "current-sensor") &&
		   !strcmp(l, "CPU Current")) {
		ads->sens.ops = &smu_cpuamp_ops;
		ads->sens.name = "cpu-current";
		if (cpuvcp == NULL) {
			DBG("wf: cpuvcp partition (%02x) not found\n",
			    SMU_SDB_CPUVCP_ID);
			goto fail;
		}
	} else if (!strcmp(c, "voltage-sensor") &&
		   !strcmp(l, "CPU Voltage")) {
		ads->sens.ops = &smu_cpuvolt_ops;
		ads->sens.name = "cpu-voltage";
		if (cpuvcp == NULL) {
			DBG("wf: cpuvcp partition (%02x) not found\n",
			    SMU_SDB_CPUVCP_ID);
			goto fail;
		}
	} else if (!strcmp(c, "power-sensor") &&
		   !strcmp(l, "Slots Power")) {
		ads->sens.ops = &smu_slotspow_ops;
		ads->sens.name = "slots-power";
		if (slotspow == NULL) {
			DBG("wf: slotspow partition (%02x) not found\n",
			    SMU_SDB_SLOTSPOW_ID);
			goto fail;
		}
	} else
		goto fail;

	v = of_get_property(node, "reg", NULL);
	if (v == NULL)
		goto fail;
	ads->reg = *v;

	if (wf_register_sensor(&ads->sens))
		goto fail;
	return ads;
 fail:
	kfree(ads);
	return NULL;
}