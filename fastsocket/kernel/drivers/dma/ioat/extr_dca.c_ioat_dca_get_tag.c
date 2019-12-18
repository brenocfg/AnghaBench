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
typedef  int u8 ;
struct ioat_dca_priv {int* tag_map; } ;
struct device {int dummy; } ;
struct dca_provider {int dummy; } ;

/* Variables and functions */
 int DCA_TAG_MAP_VALID ; 
 int IOAT_TAG_MAP_LEN ; 
 int cpu_physical_id (int) ; 
 struct ioat_dca_priv* dca_priv (struct dca_provider*) ; 

__attribute__((used)) static u8 ioat_dca_get_tag(struct dca_provider *dca,
			   struct device *dev,
			   int cpu)
{
	struct ioat_dca_priv *ioatdca = dca_priv(dca);
	int i, apic_id, bit, value;
	u8 entry, tag;

	tag = 0;
	apic_id = cpu_physical_id(cpu);

	for (i = 0; i < IOAT_TAG_MAP_LEN; i++) {
		entry = ioatdca->tag_map[i];
		if (entry & DCA_TAG_MAP_VALID) {
			bit = entry & ~DCA_TAG_MAP_VALID;
			value = (apic_id & (1 << bit)) ? 1 : 0;
		} else {
			value = entry ? 1 : 0;
		}
		tag |= (value << i);
	}
	return tag;
}