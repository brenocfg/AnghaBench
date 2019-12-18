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
struct vdso_data {int ectg_available; } ;

/* Variables and functions */
 scalar_t__ HOME_SPACE_MODE ; 
 unsigned int stfl () ; 
 scalar_t__ user_mode ; 

__attribute__((used)) static void vdso_init_data(struct vdso_data *vd)
{
	unsigned int facility_list;

	facility_list = stfl();
	vd->ectg_available =
		user_mode != HOME_SPACE_MODE && (facility_list & 1);
}