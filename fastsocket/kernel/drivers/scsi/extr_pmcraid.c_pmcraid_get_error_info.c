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
typedef  scalar_t__ u32 ;
struct pmcraid_ioasc_error {scalar_t__ ioasc_code; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct pmcraid_ioasc_error*) ; 
 struct pmcraid_ioasc_error* pmcraid_ioasc_error_table ; 

__attribute__((used)) static struct pmcraid_ioasc_error *pmcraid_get_error_info(u32 ioasc)
{
	int i;
	for (i = 0; i < ARRAY_SIZE(pmcraid_ioasc_error_table); i++) {
		if (pmcraid_ioasc_error_table[i].ioasc_code == ioasc)
			return &pmcraid_ioasc_error_table[i];
	}
	return NULL;
}