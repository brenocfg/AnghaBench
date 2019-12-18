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
typedef  unsigned long u64 ;

/* Variables and functions */
 int /*<<< orphan*/  lv1_get_logical_ppe_id (unsigned long*) ; 
 int /*<<< orphan*/  lv1_get_virtual_address_space_id_of_ppe (unsigned long,unsigned long*) ; 

__attribute__((used)) static unsigned long get_vas_id(void)
{
	u64 id;

	lv1_get_logical_ppe_id(&id);
	lv1_get_virtual_address_space_id_of_ppe(id, &id);

	return id;
}