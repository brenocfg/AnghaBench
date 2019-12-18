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
struct ar9300_eeprom {int templateVersion; } ;

/* Variables and functions */
 int N_LOOP ; 
 struct ar9300_eeprom const** ar9300_eep_templates ; 

__attribute__((used)) static const struct ar9300_eeprom *ar9003_eeprom_struct_find_by_id(int id)
{
#define N_LOOP (sizeof(ar9300_eep_templates) / sizeof(ar9300_eep_templates[0]))
	int it;

	for (it = 0; it < N_LOOP; it++)
		if (ar9300_eep_templates[it]->templateVersion == id)
			return ar9300_eep_templates[it];
	return NULL;
#undef N_LOOP
}